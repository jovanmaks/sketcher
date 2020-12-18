#include "Grid.h"
#include "Atributes.h"
#include <cmath>

namespace grid
{
        BufferData::BufferData()
        {            
        }

        BufferData::~BufferData()
        {            
        }

        float BufferData::Value ( float* values )
        {

            for(int i=0; i<colums;i++)
            {
                for(int j=0; j<rows; j++ )
                {
                values[i + j*colums]= GridValue ;
                }
            }
            return 0;
        }  

        /* X position */
        float BufferData::XPositionCoordinates ( float* Xpositions )
        {

            for(int i=0; i<heightVertex; i++)
            {
                for(int j=0; j<widthVertex; j++)
                {
                    Xpositions[ i*widthVertex + j ] = j ;
                }
            }

            return 0;
        }

        /* Y position */
        float BufferData::YPositionCoordinates ( float* Ypositions )
        {

            for(int i=0; i<heightVertex; i++)
            {
                for(int j=0; j<widthVertex; j++)
                {
                    Ypositions[ i*widthVertex + j ] = i ;
                }
            }

            return 0;            
        }

        /* Z position */
        float BufferData::ZPositionCoordinates ( float* Zpositions )
        {

            for(int i=0; i<heightVertex; i++)
            {
                for(int j=0; j<widthVertex; j++)
                {
                    Zpositions[ i*widthVertex + j ] = 0;
                }
            }

            return 0;            
        }

        float BufferData::ColorRGB ( float* rgb)
        {


             for(int i=0; i<countSingleColor/2;i++)
            {
                
                rgb[i*2] = RGB1;
                rgb[i*2 + 1] = RGB2;

            } 
            
            return 0;
        }

        float BufferData::ColorAlpha ( float* alpha )
        {
            
            for(int i=0; i<countAlfa;i++)
            {
                alpha[i] = 1;
            }

            return 0;
        }

        /* Texture coordinates */
        float BufferData::TextureCoordinates ( float* array )
        {
                /* ovo ostaje da se uradi - TODO */
                return 0;
        }
       



        //=============== BUFFER CLASS ================//
        
        Buffer::Buffer()
        {            
        }

        Buffer::~Buffer()
        {            
        }        


        float Buffer::VertexBuffer_XY(float* bufferXY)
        {       

           float* Xpositions = new float[countVerteks];
           float* Ypositions = new float[countVerteks];

            BufferData BD;
            BD.XPositionCoordinates(Xpositions);
            BD.YPositionCoordinates(Ypositions);
            
            for(int i=0; i<countCoordinatesXY/2; i++)
            {
                bufferXY[  i*2      ]= Xpositions[i] ;/* za X1 poziciju  */
                bufferXY[ (i*2) + 1 ]= Ypositions[i] ;/* za Y1 poziciju  */

            }

            return 0;    
        }


        float Buffer::VertexBuffer_XYZ(float* bufferXYZ)
        {

            float* Xpositions = new float[countVerteks];
            float* Ypositions = new float[countVerteks];
            float* Zpositions = new float[countVerteks];

            BufferData BD;
            BD.XPositionCoordinates(Xpositions);
            BD.YPositionCoordinates(Ypositions);
            BD.ZPositionCoordinates(Zpositions);

            
            for(int i=0; i<countCoordinatesXYZ/3; i++)
            {

                bufferXYZ[  i*3      ]= Xpositions[i] ;/* za X1 poziciju  */
                bufferXYZ[ (i*3) + 1 ]= Ypositions[i] ;/* za Y1 poziciju  */
                bufferXYZ[ (i*3) + 2 ]= Zpositions[i] ;/* za Z1 poziciju  */                 

            }

            return 0;    

        }


        float Buffer::VertexBuffer_XY_RGBA(float* bufferXY_RGBA)
        {            
            
            float* Xpositions = new float[countVerteks];
            float* Ypositions = new float[countVerteks]; 

            float* rgb = new float[countSingleColor];            
            float* A   = new float[countAlfa];


            BufferData BD;
            BD.XPositionCoordinates(Xpositions);
            BD.YPositionCoordinates(Ypositions);
            BD.ColorRGB(rgb);
            BD.ColorAlpha(A);
            


            for(int i=0; i<countAllXY/6; i++)
            {
                bufferXY_RGBA[  i*6      ]= Xpositions[i] ;/* za X1 poziciju  */
                bufferXY_RGBA[ (i*6) + 1 ]= Ypositions[i] ;/* za Y1 poziciju  */
                bufferXY_RGBA[ (i*6) + 2 ]= rgb[i] ;/* za Y1 poziciju  */
                bufferXY_RGBA[ (i*6) + 3 ]= rgb[i] ;/* za Y1 poziciju  */
                bufferXY_RGBA[ (i*6) + 4 ]= rgb[i] ;/* za Y1 poziciju  */
                bufferXY_RGBA[ (i*6) + 5 ]= A[i] ;/* za Y1 poziciju  */

            }

            return 0;    
        }

        float Buffer::VertexBuffer_XYZ_RGBA(float* bufferXYZ_RGBA)
        {

            
            float* Xpositions = new float[countVerteks];
            float* Ypositions = new float[countVerteks];
            float* Zpositions = new float[countVerteks];


            float* rgb = new float[countSingleColor];            
            float* A = new float[countAlfa];


            BufferData BD;
            BD.XPositionCoordinates(Xpositions);
            BD.YPositionCoordinates(Ypositions);
            BD.ColorRGB(rgb);
            BD.ColorAlpha(A);
            


            for(int i=0; i<countAllXYZ/7; i++)
            {
                bufferXYZ_RGBA[  i*7      ]= Xpositions[i] ;/* za X1 poziciju  */
                bufferXYZ_RGBA[ (i*7) + 1 ]= Ypositions[i] ;/* za Y1 poziciju  */
                bufferXYZ_RGBA[ (i*7) + 2 ]= Zpositions[i] ;/* za Y1 poziciju  */

                bufferXYZ_RGBA[ (i*7) + 3 ]= rgb[i] ;/* za Y1 poziciju  */
                bufferXYZ_RGBA[ (i*7) + 4 ]= rgb[i] ;/* za Y1 poziciju  */
                bufferXYZ_RGBA[ (i*7) + 5 ]= rgb[i] ;/* za Y1 poziciju  */
                bufferXYZ_RGBA[ (i*7) + 6 ]= A[i] ;/* za Y1 poziciju  */


            }

            return 0; 
        }

        unsigned int Buffer::IndexBuffer( std::vector<unsigned int>& indices )
        {
           
             // indices.reserve(2*(width-1) * (height-1));

            for(int i = 0; i<colums; i++)
            {
                for(int j = 0; j<rows; j++)
                {

                int  xPos = j + i*(rows+1);

                indices.push_back(xPos);
                indices.push_back(xPos+1);
                indices.push_back(xPos+rows +1);


                indices.push_back(xPos+1);
                indices.push_back(xPos + rows+1);        
                indices.push_back(xPos + rows+2);        

                }
            }
                      
          return 0;
        }
    

        unsigned int Buffer::IndexBufferWires( std::vector<unsigned int>& indices )
        {
           
             // indices.reserve(2*(width-1) * (height-1));

            for(int i = 0; i<colums; i++)
            {
                for(int j = 0; j<rows; j++)
                {

                int  xPos = j + i*(rows+1);

                indices.push_back(xPos);
                indices.push_back(xPos+1);
                indices.push_back(xPos+rows +1);


                indices.push_back(xPos+1);
                indices.push_back(xPos + rows+1);        
                indices.push_back(xPos + rows+2);        

                }
            }
                      
          return 0;
        }
    
        unsigned int Buffer::IndexBufferWiresSecundary(std::vector<unsigned int>& indices)
        {
            for(int i = 0; i<colums; i = i+2)
            {
                for(int j = 0; j<rows; j = j+2)
                {

                int  xPos = j + i*(rows+1);

                indices.push_back(xPos);
                indices.push_back(xPos+2);
                indices.push_back(xPos+rows*2 +2);


                indices.push_back(xPos+2);
                indices.push_back(xPos + rows*2 + 2);        
                indices.push_back(xPos + rows*2 + 4);        

                }
            }

            return 0;
        }
        /* ovo treba da modifikujes da bude dinamican da moze da se poveca jer je hardcodded */
        unsigned int Buffer::IndexBufferElement( double mouseX, double mouseY, unsigned int* Igraliste )
        {
            /* dimenzije celije u pixelima */
            double celijaX = ScreenWidth/rows;      
            double celijaY = ScreenHeight/colums;

            unsigned int Ix = mouseX/celijaX;//treba da zaokruzis ovo na donju
            unsigned int Iy = (ScreenHeight - mouseY)/celijaY;//treba da zaokruzis ovo na donju
           
            //formula za racunanje ugaonog indeksa
            unsigned int I0= Ix + Iy*(rows+1);//prvi indeks. Donji lijevi


            for(int i = 0; i<1; i++)
            {
            Igraliste[i]   = I0;
            Igraliste[i+1] = I0+1;
            Igraliste[i+2] = I0+1+rows ;
            
            Igraliste[i+3] = I0+1;
            Igraliste[i+4] = I0+1+rows;
            Igraliste[i+5] = I0+1+rows + 1;
            }

            return 0;

        }

        unsigned int Buffer::IndexBufferElement2( double mouseX, double mouseY, unsigned int* Igraliste )
        {
            /* dimenzije celije u pixelima */
            double celijaX = ScreenWidth/rows;      
            double celijaY = ScreenHeight/colums;

            unsigned int Ix = mouseX/celijaX;//treba da zaokruzis ovo na donju
            unsigned int Iy = (ScreenHeight - mouseY)/celijaY;//treba da zaokruzis ovo na donju
           
            //formula za racunanje ugaonog indeksa
            unsigned int I0= Ix + Iy*(rows+1);//prvi indeks. Donji lijevi


            for(int i = 0; i<1; i++)
            {
            Igraliste[i]   = I0;
            Igraliste[i+1] = I0+2;
            Igraliste[i+2] = I0+2+rows*2 ;
            
            Igraliste[i+3] = I0+2;
            Igraliste[i+4] = I0+2+rows*2;
            Igraliste[i+5] = I0+2+rows*2 + 2;
            }

            return 0;

        }


        unsigned int Buffer::IndexBufferElement3 (double mouseXStatic, double mouseYStatic, double mouseXDynamic, double mouseYDynamic, unsigned int* Igraliste)
        {

            double celijaX = ScreenWidth/rows;      
            double celijaY = ScreenHeight/colums;

            unsigned int Ix = mouseXStatic/celijaX;//treba da zaokruzis ovo na donju
            unsigned int Iy = (ScreenHeight - mouseYStatic)/celijaY;//treba da zaokruzis ovo na donju
           
            unsigned int Ix2 = mouseXDynamic/celijaX;//treba da zaokruzis ovo na donju
            unsigned int Iy2 = (ScreenHeight - mouseYDynamic)/celijaY;//treba da zaokruzis ovo na donju

            //formula za racunanje ugaonog indeksa
            unsigned int I0= Ix + Iy*(rows+1);//prvi indeks. Donji lijevi
            unsigned int I02= Ix2 + Iy*(rows+1);//prvi indeks. Donji lijevi
            unsigned int I03= Ix + Iy2*(rows+1);//prvi indeks. Donji lijevi


            //Uslovi za orjentisanje
            //1.Horizontalni uslovi

            int visina = mouseYStatic - mouseYDynamic;
            int visinaABS = abs(visina);

            int sirina = mouseXDynamic - mouseXStatic;
            int sirinaABS = abs(sirina);

            if( (visinaABS) <= (sirinaABS) ) 
            {
                for( int i = 0; i<1; i++)
                {
                Igraliste[i]   = I0;
                Igraliste[i+1] = I02+1;
                Igraliste[i+2] = I0+1+rows;
                
                Igraliste[i+3] = I02+1;
                Igraliste[i+4] = I0+1+rows;
                Igraliste[i+5] = I02+1+rows + 1;
                }

            }else if(  (visinaABS) > (sirinaABS) ){

                for( int i = 0; i<1; i++)
                {
                Igraliste[i]   = I0;
                Igraliste[i+1] = I0+1;
                Igraliste[i+2] = I03+1+rows;
                
                Igraliste[i+3] = I0+1;
                Igraliste[i+4] = I03+1+rows;
                Igraliste[i+5] = I03+1+rows + 1;
                }
            }
            
            return 0;
        }

        unsigned int Buffer::IndexBufferRooler ( double mouseX,double mouseY, unsigned int* Igraliste )
        {
            
            // Ovo ne moze raditi jer si ubaicio u bufer vec tacke i samo njih mozes koristiti
            //potreban bi ti bio novi bufer i da kupis te indekse jer u ovom indeksi nisu
            //zadovoljavajuci
            // unsigned int I0= 0;
            // unsigned int I1= mouseX;

            /* for(int i = 0; i<1; i++)
            {
            Igraliste[i]      = I0;
            Igraliste[i +1]   = I1;
            } */


            return 0;
        }

    
        /* Ovo je ostavljeno da ima kako se radi mergovanje nizova */
        unsigned int Buffer::IndexBufferMerged( int countOne, int countTwo, unsigned int* Base, unsigned int* Element, unsigned int* Memory )
        {      
            int countMerged = countOne + countTwo;
                
            for (int i = 0; i<countTwo; i++)
             {
                 Memory[i] = Element[i];         

             }


             for(int j=countTwo; j<countMerged; j++)
             {
                //  Memory[j] = Base[j];
             }



            //  for (int i = 0; i<countOne; i++)
            //  {
            //     //  Base[i]=22;
            //      Merged[i] = Base[i];
            //  }


        
            //  for (int i = 0; i<countTwo; i++)//count element je 6 hard coded
            //  {

            //      Merged[i]= Element[i];
            //      // Element[i]=44;
            //      for(int j=countOne; j<countMerged; j++)
            //      {
            //          // Merged[j] = Element[i];
            //          Merged[j] = Element[j];
            //      }

            //  }
                   
            return 0;
        }

        unsigned int Buffer::IndexBufferMemory( double mouseX, double mouseY, int brojac, unsigned int* Igraliste )
        {

            double celijaX = ScreenWidth/rows;      
            double celijaY = ScreenHeight/colums;

            double  Ix = mouseX/celijaX;//treba da zaokruzis ovo na donju
            double res1;
            res1 = floor( Ix);

            double  Iy = (ScreenHeight - mouseY)/celijaY;//treba da zaokruzis ovo na donju
            double  res2;
            res2 = floor(Iy);
            //formula za racunanje ugaonog indeksa
            unsigned int I0= res1 + res2*(rows+1);//prvi indeks. Donji lijevi
            unsigned int I1=I0 +1;
            unsigned int I2=I0 +1 + rows;

            unsigned int I3=I0 +1;
            unsigned int I4=I0 +1 + rows;
            unsigned int I5=I0 +1 + rows + 1;       

            /* Valgrind izgleda ovo izbacuje kao invalid write */
            if(brojac == 1 )
            {
            Igraliste[0]= I0;
            Igraliste[1]= I1;
            Igraliste[2]= I2;
 
            Igraliste[3]= I3;
            Igraliste[4]= I4;
            Igraliste[5]= I5;
            }else{

            Igraliste[brojac*6 -6]= I0;
            Igraliste[brojac*6 -5]= I1;
            Igraliste[brojac*6 -4]= I2;
 
            Igraliste[brojac*6 -3]= I3;
            Igraliste[brojac*6 -2]= I4;
            Igraliste[brojac*6 -1]= I5;
            }

         
         return 0;
        }

        unsigned int Buffer::IndexBufferMemory2( double mouseX, double mouseY, int brojac, unsigned int* Igraliste )
        {

            double celijaX = ScreenWidth/rows;      
            double celijaY = ScreenHeight/colums;

            double  Ix = mouseX/celijaX;//treba da zaokruzis ovo na donju
            double res1;
            res1 = floor( Ix);

            double  Iy = (ScreenHeight - mouseY)/celijaY;//treba da zaokruzis ovo na donju
            double  res2;
            res2 = floor(Iy);

           
             //formula za racunanje ugaonog indeksa
            unsigned int I0= res1 + res2*(rows+1);//prvi indeks. Donji lijevi
            unsigned int I1=I0 +2;
            unsigned int I2=I0 +2 + rows*2;

            unsigned int I3=I0 +2;
            unsigned int I4=I0 +2 + rows*2;
            unsigned int I5=I0 +2 + rows*2 + 2;       


            /* Valgrind izgleda ovo izbacuje kao invalid write */
            //Videi da nije registrovao indekse kao nesto sto nije integer
            //Ubacen je ovaj uslov na pocetku jer izgleda se nulti mora rucno definisati 
            //ako ide preko brojaca izgleda neko njesra
            //ali ni to nije rijesilo bug
            if(brojac ==1 )
            {
            Igraliste[0]= I0;
            Igraliste[1]= I1;
            Igraliste[2]= I2;
 
            Igraliste[3]= I3;
            Igraliste[4]= I4;
            Igraliste[5]= I5;
            }else{
            Igraliste[brojac*6 -6]= I0;
            Igraliste[brojac*6 -5]= I1;
            Igraliste[brojac*6 -4]= I2;
 
            Igraliste[brojac*6 -3]= I3;
            Igraliste[brojac*6 -2]= I4;
            Igraliste[brojac*6 -1]= I5;
         
            }
            return 0;
        }

         unsigned int Buffer::IndexBufferGreda (double mouseXStatic, double mouseYStatic, double mouseXDynamic, double mouseYDynamic, int brojac, unsigned int* Igraliste)
        {

            double celijaX = ScreenWidth/rows;      
            double celijaY = ScreenHeight/colums;

            unsigned int Ix = mouseXStatic/celijaX;//treba da zaokruzis ovo na donju
            double res1;
            res1 = floor( Ix);

            unsigned int Iy = (ScreenHeight - mouseYStatic)/celijaY;//treba da zaokruzis ovo na donju
            double  res2;
            res2 = floor(Iy);
           
            unsigned int Ix2 = mouseXDynamic/celijaX;//treba da zaokruzis ovo na donju
            double  res3;
            res3 = floor(Ix2);

            unsigned int Iy2 = (ScreenHeight - mouseYDynamic)/celijaY;//treba da zaokruzis ovo na donju
            double  res4;
            res4 = floor(Iy2);


            //formula za racunanje ugaonog indeksa
            unsigned int I0= res1 + res2*(rows+1);//prvi indeks. Donji lijevi
            unsigned int I02= res3 + res2*(rows+1);//prvi indeks. Donji lijevi
            unsigned int I03= res1 + res4*(rows+1);//prvi indeks. Donji lijevi


            //Uslovi za orjentisanje
            //1.Horizontalni uslovi

            int visina = mouseYStatic - mouseYDynamic;
            int visinaABS = abs(visina);

            int sirina = mouseXDynamic - mouseXStatic;
            int sirinaABS = abs(sirina);

            if( (visinaABS) <= (sirinaABS) ) 
            {
                    //ako ces da popravlkjas kad ide na lijevo
                    //onda moras da das uslove kad je lijevo kad desno pa da 
                    //modifikujes ove dinamicne indekse
                Igraliste[brojac*6 -6]   = I0;
                Igraliste[brojac*6 -5] = I02+1;
                Igraliste[brojac*6 -4] = I0+1+rows;
                
                Igraliste[brojac*6 -3] = I02+1;
                Igraliste[brojac*6 -2] = I0+1+rows;
                Igraliste[brojac*6 -1] = I02+1+rows + 1;

            }else if(  (visinaABS) > (sirinaABS) ){

                Igraliste[brojac*6 -6]   = I0;
                Igraliste[brojac*6 -5] = I0+1;
                Igraliste[brojac*6 -4] = I03+1+rows;
                
                Igraliste[brojac*6 -3] = I0+1;
                Igraliste[brojac*6 -2] = I03+1+rows;
                Igraliste[brojac*6 -1] = I03+1+rows + 1;

            }
            


            return 0;

        }

         unsigned int Buffer::IndexBufferEraser (double mouseXStatic, double mouseYStatic, double mouseXDynamic, double mouseYDynamic, int brojac, unsigned int* Igraliste)
        {

            return 0;
        }

} // namespace grid
