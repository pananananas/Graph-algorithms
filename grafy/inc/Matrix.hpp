#ifndef Macierz_hpp
#define Macierz_hpp
#include "Include.hpp"

struct VertexM {
    
    int      Wartosc;
    VertexM  *Adres;
    int      ID;
    
    VertexM() = default;
    VertexM (int id, int W, VertexM *Ad) {
        Wartosc = W; ID = id; Adres = Ad; };
    void SetAdress(VertexM *ad)          {
        Adres = ad;
    };
    int  ReturnID()                      {
        return ID; };
    ~VertexM() = default;
};


struct EdgeM {
    
    int      Wartosc;
    EdgeM    *Adres;
    VertexM  *Start;
    VertexM  *Koniec;
    
    EdgeM()                        {
        Wartosc = 0; };
    EdgeM(int W, EdgeM *ad)        {
        Wartosc = W; Adres = ad; };
    EdgeM(int W, EdgeM *ad, VertexM *w, VertexM *v) {
        Wartosc = W;
        this -> Adres   = ad;
        this -> Start   = w;
        this -> Koniec  = v;
    };
    void     SetAdjacency(VertexM *w, VertexM *v)   {
        Start = w;
        Koniec = v;
    };
    VertexM* Opposite(VertexM *v)  {
        if (Start == v)     return Koniec;
        else                return Start;
    };
    void     SetAdress(EdgeM *ad)  {
        Adres = ad;
    };
    void     WyswietlWageEdge()    {
        std:: cout << this -> Wartosc << ", "; };
    void     UstawWage(int W)      {
        Wartosc = W;
    };
    int      ZwrocWage()           {
        return this -> Wartosc; };
    ~EdgeM() = default;
};


class AdjacencyMatrix {
    
    int Rozmiar;  // Czyli ilość wierzchołków
    int Gestosc;
    int IlKrawedzi;
    
    VertexM  *VertArr;
    EdgeM    *EdgeArr;
    EdgeM    ***AdjMatrix;
    
public:
    AdjacencyMatrix()                          {
        this -> VertArr   = NULL;
        this -> EdgeArr   = NULL;
        this -> AdjMatrix = NULL;
    };
    AdjacencyMatrix(int W, int G)              {
        
        Rozmiar     = W;
        Gestosc     = G;
        IlKrawedzi  = 0;
        int KrawTmp = 0;
        int MaxIlKrawedzi = (Gestosc * Rozmiar * (Rozmiar-1)) / 2;
        
        std:: random_device dev;
        std:: mt19937 rng(dev());
        std:: uniform_int_distribution<std::mt19937::result_type> dist6(1,99999);
        
        bool TrueFalse[MaxIlKrawedzi];
        for (int i = 0 ; i < MaxIlKrawedzi; ++i) {
            TrueFalse[i] = ( dist6(rng) % 100 ) < Gestosc;    // Na dany procent da 1
            if (TrueFalse[i] == 1) ++IlKrawedzi;
        }
        
        this -> VertArr   = new VertexM[Rozmiar];
        this -> EdgeArr   = new EdgeM[IlKrawedzi];
        this -> AdjMatrix = new EdgeM**[Rozmiar];
        
        std:: uniform_int_distribution<std::mt19937::result_type> dist7(1,Rozmiar);
        for (int i = 0; i < Rozmiar; ++i)                   // Wypełniam wierzchołki
            VertArr[i] = VertexM(i, dist6(rng), &VertArr[i]);
        
        for (int i = 0; i < Rozmiar; ++i) {                 // Inicjuję rozmiar macierzy i wypełniam Nullami
            AdjMatrix[i] = new EdgeM*[Rozmiar];
            for (int j = 0; j < Rozmiar; ++j)
                    AdjMatrix[i][j] = NULL;
        }
        
        std:: uniform_int_distribution<std::mt19937::result_type> dist8(1,IlKrawedzi);
        for (int i = 0; i < Rozmiar; ++i)                   // Tworzę połączenie tam gdzie powinno być
        for (int j = 0; j < Rozmiar; ++j) {
            if (j-i >= 1 &&  TrueFalse[KrawTmp] != 0) {     // Jest połączenie, wypełniam krawedzie i macierz
                EdgeArr[KrawTmp] = EdgeM(dist8(rng), &EdgeArr[i], &VertArr[j], &VertArr[i]);
                AdjMatrix[i][j]  = &EdgeArr[KrawTmp];
                AdjMatrix[j][i]  = &EdgeArr[KrawTmp];
            }
            ++KrawTmp;
        }
        
//        std:: cout << " Tmp: " << KrawTmp << std:: endl;    // Debug
//        std:: cout << " Wla: " << IlKrawedzi << std:: endl;
//        std:: cout << " Max: " << MaxIlKrawedzi << std:: endl;
    };
    void Create(int W, int G)                  {
        
        Rozmiar     = W;
        Gestosc     = G;
        IlKrawedzi  = 0;
        int KrawTmp = 0;
        int MaxIlKrawedzi = (Gestosc * Rozmiar * (Rozmiar-1)) / 2;
        
        std:: random_device dev;
        std:: mt19937 rng(dev());
        std:: uniform_int_distribution<std::mt19937::result_type> dist6(1,1000);
        
        bool* TrueFalse = new bool[MaxIlKrawedzi];
        for (int i = 0 ; i < MaxIlKrawedzi; ++i) {
            TrueFalse[i] = ( dist6(rng) % 100 ) < Gestosc;    // Na dany procent da 1
            if (TrueFalse[i] == 1) ++IlKrawedzi;
        }
        
        this -> VertArr   = new VertexM[Rozmiar];
        this -> EdgeArr   = new EdgeM[IlKrawedzi];
        this -> AdjMatrix = new EdgeM**[Rozmiar];
        
        std:: uniform_int_distribution<std::mt19937::result_type> dist7(1,Rozmiar);
        for (int i = 0; i < Rozmiar; ++i)                   // Wypełniam wierzchołki
            VertArr[i] = VertexM(i, dist6(rng), &VertArr[i]);
        
        for (int i = 0; i < Rozmiar; ++i) {                 // Inicjuję rozmiar macierzy i wypełniam Nullami
            AdjMatrix[i] = new EdgeM*[Rozmiar];
            for (int j = 0; j < Rozmiar; ++j)
                    AdjMatrix[i][j] = NULL;
        }
        
        std:: uniform_int_distribution<std::mt19937::result_type> dist8(1,IlKrawedzi);
        for (int i = 0; i < Rozmiar; ++i)                   // Tworzę połączenie tam gdzie powinno być
        for (int j = 0; j < Rozmiar; ++j) {
            if (j-i >= 1 &&  TrueFalse[KrawTmp] != 0) {     // Jest połączenie, wypełniam krawedzie i macierz
//                int x =dist8(rng);
//                std:: cout << x << std::endl;
                EdgeArr[KrawTmp] = EdgeM(dist8(rng), &EdgeArr[i], &VertArr[j], &VertArr[i]);
                AdjMatrix[i][j]  = &EdgeArr[KrawTmp];
                AdjMatrix[j][i]  = &EdgeArr[KrawTmp];
            }
            ++KrawTmp;
        }
            
//        std:: cout << " Tmp: " << KrawTmp << std:: endl;    // Debug
//        std:: cout << " Wla: " << IlKrawedzi << std:: endl;
//        std:: cout << " Max: " << MaxIlKrawedzi << std:: endl;
    };
    bool   AreAdjacent(int i, int j)           {
        if (AdjMatrix[i][j] != NULL)    return true;
        else                            return false;
    };
    EdgeM* GetAdjacency(int i, int j)          {
        if (AdjMatrix[i][j] != NULL)    return AdjMatrix[i][j];
        else                            return NULL;
    };
    int    GetEdgeLength(int i, int j)         {
        if (AdjMatrix[i][j]!= NULL)     return AdjMatrix[i][j]->ZwrocWage();
        else                            return 0;
    };
    int    GetSize()                           {
        return Rozmiar;
    };
    void   WyswietlMacierz(std::ostream &strm) {
        for (int i = 0; i < Rozmiar; ++i) {
            for (int j = 0; j< Rozmiar; ++j)
                strm << AdjMatrix[i][j] << ", ";
            strm << std::endl;
        }
    };
    void   WyswietlWage(std::ostream &strm)    {
        for (int i = 0; i < Rozmiar; ++i) {
            for (int j = 0; j< Rozmiar; ++j)
                if (AdjMatrix[i][j]!= NULL)
                    std:: cout << AdjMatrix[i][j]->ZwrocWage() << ", ";
                else
                    std:: cout << "0, ";
            strm << std::endl;
        }
    };
    ~AdjacencyMatrix() =default;
};

#endif
