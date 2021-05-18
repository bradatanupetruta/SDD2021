#include <stdio.h>
#include <tchar.h>
#include <memory.h>
#include <stdlib.h>

/*       huffman trees            */
typedef struct hufftree {
    unsigned int freq;       //s1 freq
    unsigned char s1;        //0...255:codes       left symb
    unsigned char s2;        //                    right symb
    hufftree* pleft;         //0
    hufftree* pright;        //1
    hufftree* parent;        //parent node
} *PHTREE;

typedef struct huffsymbol {
    unsigned int size;       //symbol size in bits
    __int64 symb;            //max 256 bits
} *PSYMB;

/*       huffman file headers            */
typedef struct huffheader {
    char magic[4];           //'HUFF'
    int symnum;              //total symbnum
    int uncmpsize;           //uncompressed file size
    int cmpsize;             //compressed file size
} *PHUFFHDR;

typedef struct symbheader {
    unsigned int freq;       //its freq
    unsigned char symb;      //symbol
} *PSYMBHDR;

class Huffman
{
public:
    Huffman() {};
    void encode(unsigned char* dest, int& csize, unsigned char* sour, int usize);
    void decode(unsigned char* dest, int& usize, unsigned char* sour);
    inline int get_uncompressed_size(unsigned char* sour);
protected:
private:
    Huffman(const Huffman& huffman);
    const Huffman& operator=(const Huffman& huffman);

    PHTREE temptree;                              //tmass1 first tree
    PHTREE htree;                                 //tmass2 second huff tree
    PSYMB hsymbol;                                //smass symbols codebook

    unsigned char tmass1[256 * sizeof(hufftree)];             //first tree with freq codes
    unsigned char tmass2[256 * sizeof(hufftree)];             //last built tree
    unsigned char smass[256 * sizeof(huffsymbol)];            //symbols codebook buffer [code][size] pairs

    unsigned char* psour;                                  //source pointer
    unsigned char* pdest;                                  //dest pointer

    PHUFFHDR pheader;                              //huffman file header
    PSYMBHDR psheader;                             //[ freq ][C] pairs

    int filesize;                                 //uncompressed file size
    int symnum;                                   //total different symbols
    int bitslast;

    static int __cdecl compare(const void* a, const void* b);    //for sorting routine

    void storetree(void);                         //memory and huff headers init
    void buildtree(void);                         //htree building
    void buildbook(void);                         //build codebook [code][size] pairs
    void writesymb(int c);                        //write codebook symbol

    void readtree(void);                          //read headers and get freqs
    unsigned char readsymb();                     //read symbol from htree
    inline int getnextbit();                      //get bits from sour

};

inline int Huffman::get_uncompressed_size(unsigned char* sour)
{
    pheader = (PHUFFHDR)sour;
    return pheader->uncmpsize;
}

/*             get bits from sour             */
inline int Huffman::getnextbit()
{
    if (bitslast) {
        return 0x1 & (*psour >> (--bitslast));
    }
    else {
        psour++;
        bitslast = 8;
        return 0x1 & (*psour >> (--bitslast));
    }
}

/*    IN sour = uncompressed code usize BYTES OUT dest = compressed code csize BYTES     */
void Huffman::encode(unsigned char* dest, int& csize, unsigned char* sour, int usize)
{
    pheader = (PHUFFHDR)dest;     //huff header
    psour = sour;                //sour buffer
    pdest = dest;                //dest buffer
    filesize = usize;            //uncompressed file size
    csize = 0;                   //fault protection
    symnum = 0;
    bitslast = 8;
    storetree();                 //get freqs and store headers
    buildtree();                 //build htree
    buildbook();                 //build codebook
    for (int i = 0; i < filesize; i++)
        writesymb(*psour++);
    csize = int((pdest - dest) + 1);
    pheader->cmpsize = csize;
}

/*    IN sour = compressed huffman frame OUT dest = uncompressed code usize BYTES     */
void Huffman::decode(unsigned char* dest, int& usize, unsigned char* sour)
{
    pheader = (PHUFFHDR)sour;     //huff header
    psour = sour;                //sour buffer
    pdest = dest;                //dest buffer
    usize = 0;                   //fault protection
    bitslast = 8;
    readtree();                  //read headers and get freqs
    buildtree();                 //build tree
    while (filesize) {
        *pdest++ = readsymb();
        filesize--;
    }
    usize = int(pdest - dest);
}

/*                           HUFF ENCODING ROUTINES                              */
/*         init tree buffers fill headers                             */
void Huffman::storetree(void)
{
    /*               memory init                           */
    memset(tmass1, 0, 256 * sizeof(hufftree));
    memset(tmass2, 0, 256 * sizeof(hufftree));
    memset(smass, 0, 256 * sizeof(huffsymbol));

    temptree = (PHTREE)tmass1;
    htree = (PHTREE)tmass2;
    hsymbol = (PSYMB)smass;

    for (int i = 0; i < 256; i++) temptree[i].s1 = i;               //initilize symbols
    for (int i = 0; i < filesize; i++) temptree[psour[i]].freq++;   //get symb frequencies
    for (int i = 0; i < 256; i++)
        if (temptree[i].freq) symnum++;        //get total symbols

    qsort((void*)temptree, 256, sizeof(hufftree), &compare);      //sort temptree

    /*               headers init                           */
    memcpy(pheader->magic, "HUFF", 4);
    pheader->symnum = symnum;
    pheader->uncmpsize = filesize;
    pheader->cmpsize = 0;

    pdest += sizeof(huffheader);

    /*   make [  freq  ][C] pairs    */
    for (int i = 0; i < symnum; i++) {
        psheader = (PSYMBHDR)pdest;
        psheader->symb = temptree[i].s1;
        psheader->freq = temptree[i].freq;

        pdest += 5;     //sizeof(PSYMBFRQ)
    }
    *pdest = 0;
}

/*         build htree from temptree                */
void Huffman::buildtree()
{
    /*        special case symnum = 1   */
    if (symnum == 1) {
        hsymbol[psour[0]].size = 1;
        return;
    }
    /*        build 1 & 2 trees        */
    for (int i = symnum - 2; i >= 0; i--) {
        if (temptree[i].parent) {                    //if it is compound node yet
            htree[i].pleft = temptree[i].parent;        //to another node 0
            htree[i].pleft->parent = &htree[i];
        }
        else
            htree[i].s1 = temptree[i].s1;               //to final symbol 0

        if (temptree[i + 1].parent) {
            htree[i].pright = temptree[i + 1].parent;     //to another node 1
            htree[i].pright->parent = &htree[i];
        }
        else
            htree[i].s2 = temptree[i + 1].s1;	           //to final symbol 1

        if (i) {
            temptree[i].freq += temptree[i + 1].freq;     //[i]+[i+1] frequencies for new [i] node
            temptree[i].parent = &htree[i];             //[i] becomes a node
            temptree[i + 1].freq = 0;                     //[i+1] destroyed

            qsort((void*)temptree, (i + 1), sizeof(hufftree), &compare);
        }
    }
}

/*         build codebook from htree        */
void Huffman::buildbook()
{
    unsigned char c;
    PHTREE parent, child;

    /*     build symbols from htree    */
    for (int i = symnum - 2; i >= 0; i--) {
        if (!htree[i].pleft) {            //0bit symbol
            c = htree[i].s1;
            hsymbol[c].size++;

            child = &htree[i];
            parent = child->parent;
            while (parent) {
                if (parent->pleft == child)              //add 0 to symb code
                    hsymbol[c].size++;
                if (parent->pright == child)		       //add 1 to symb code
                    hsymbol[c].symb |= __int64(1 << hsymbol[c].size++);

                child = parent;                    //child becomes a parent
                parent = child->parent;            //parent becomes 'childs' parent
            }
        }
        if (!htree[i].pright) {           //1bit symbol
            c = htree[i].s2;
            hsymbol[c].symb |= __int64(1 << hsymbol[c].size++);

            child = &htree[i];
            parent = child->parent;
            while (parent) {
                if (parent->pleft == child)              //add 0 to symb code
                    hsymbol[c].size++;
                if (parent->pright == child)             //add 1 to symb code
                    hsymbol[c].symb |= __int64(1 << hsymbol[c].size++);

                child = parent;                    //child becomes a parent
                parent = child->parent;            //parent becomes 'childs' parent
            }
        }
    }
}

/*         write codebook symbol to dest    */
void Huffman::writesymb(int c)
{
    for (unsigned int i = 1; i <= hsymbol[c].size; i++) {
        *pdest |= ((0x1 & (hsymbol[c].symb >> (hsymbol[c].size - i))) << (--bitslast));

        if (bitslast == 0) {
            *(++pdest) = 0;
            bitslast = 8;
        }
    }
}

/*                           HUFF DECODING ROUTINES                              */
/*         read huff headers and get freqs        */
void Huffman::readtree()
{
    /*               memory init                    */
    memset(tmass1, 0, 256 * sizeof(hufftree));
    memset(tmass2, 0, 256 * sizeof(hufftree));

    temptree = (PHTREE)tmass1;
    htree = (PHTREE)tmass2;

    filesize = pheader->uncmpsize;
    symnum = pheader->symnum;
    psour += sizeof(huffheader);

    /*       get freqs      */
    for (int i = 0; i < symnum; i++) {
        psheader = (PSYMBHDR)psour;
        temptree[i].freq = psheader->freq;
        temptree[i].s1 = psheader->symb;

        psour += 5;      //sizeof(PSYMBFRQ)
    }
}

/*         decode huff symbol by bit from sour        */
unsigned char Huffman::readsymb()
{
    PHTREE node = &htree[0];

    while (1) {
        if (getnextbit()) {           //next right node
            if (node->pright)
                node = node->pright;
            else
                return node->s2;
        }
        else {              //next left node
            if (node->pleft)
                node = node->pleft;
            else
                return node->s1;
        }
    }
}

/*         compare for qsort()              */
int __cdecl Huffman::compare(const void* a, const void* b)
{
    PHTREE t1 = (PHTREE)a;
    PHTREE t2 = (PHTREE)b;

    if (t1->freq == t2->freq) return 0;
    else return ((t1->freq < t2->freq) ? 1 : -1);
}

int get_file_size(FILE* fp);

int _tmain(int argc, _TCHAR* argv[])
{
    FILE* source_file, * dest_file;
    unsigned char* sour, * dest;
    int usize, csize;
    if (argc != 4) {
        wprintf(L" bad arguments.\n");
        wprintf(L"  huffman.exe e sourfile destfile\n");
        wprintf(L"  huffman.exe d sourfile destfile\n");
        exit(1);
    }
    else if ((source_file = _wfopen(argv[2], L"rb")) == NULL) {
        wprintf(L"bad file %s.\n", argv[2]);
        exit(1);
    }
    else if ((dest_file = _wfopen(argv[3], L"wb")) == NULL) {
        wprintf(L"bad file %s.\n", argv[3]);
        exit(1);
    }
    else {

        Huffman huffman;

        if (!wcscmp(argv[1], L"e"))
        {
            usize = get_file_size(source_file);

            sour = new unsigned char[usize];
            dest = new unsigned char[usize];
            usize = (int)fread(sour, 1, usize, source_file);

            huffman.encode(dest, csize, sour, usize);

            fwrite(dest, 1, csize, dest_file);
            wprintf(L" cmpression ration: %.2f\n", (float)usize / (float)csize);
        }
        else if (!wcscmp(argv[1], L"d"))
        {
            csize = get_file_size(source_file);

            sour = new unsigned char[csize];
            csize = fread(sour, 1, csize, source_file);

            dest = new unsigned char[huffman.get_uncompressed_size(sour)];

            huffman.decode(dest, usize, sour);

            fwrite(dest, 1, usize, dest_file);
        }
        else
        {
            wprintf(L"bad argument %s.\n", argv[4]);
            exit(1);
        }
        fclose(source_file);
        fclose(dest_file);
    }
    return 0;
}

int get_file_size(FILE* fp)
{
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return size;
}




