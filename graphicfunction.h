//
//  graphicfunction.h
//  
//
//  Created by Yves BAZIN on 11/01/18.
//

#ifndef graphicfunction_h
#define graphicfunction_h
const float pi = 3.14159265359;

void pixOn(byte x,byte y)
{
    PixelOn( x, y, Color);
}

void pixOnR(byte x,byte y,CRGB color)
{
    CRGB color2=color;
    if(y==0 or y>=24)
    {
        
        color2.b=color.b;
        color2.r=color.g;
        color2.g=color.r;
    }
    
            
    PixelOn( x, y, color2);
}



void BresenhamEntier(int x0, int y0,int x1, int y1)
{
    if(x0>x1)
    {
        int s=x0;
        x0=x1;
        x1=s;
        s=y0;
        y0=y1;
        y1=s;
    }
    int x;
    int y = y0;
    int dx = x1 - x0;
    int dy = y1 - y0;
    int incrE = 2 * dy ;
    int incrNE = 2 * (dy - dx);
    int e = 2 * dy - dx;
    for(x = x0; x <= x1 ; x++){
        pixOn(x, y);
        if(e >= 0){
            y += 1;
            e += incrNE;
        } else
            e += incrE;
    }
    } /* fin BresenhamEntier */


void ligne(short x1,short y1,short x2,short y2,CRGB color)
{
    short err, a, dx, dy;
    
    dx = x2 - x1 ;
    dy = y2 - y1 ;
    err = -dx>>1 ;
    x2 -= x1 ;
    
    do
    {
        pixOnR((byte)x1,(byte)y1,color);
        
        err += dy ;
        if(err > 0)
        {
            err -= dx ;
            y1++ ;
        }
        
        x1++ ;
    }while(x2--);
}

CRGB line[LED_WIDTH];

void memfill(void *dest, size_t destsize, size_t elemsize) {
    char   *nextdest = (char *) dest + elemsize;
    size_t movesize, donesize = elemsize;
    
    destsize -= elemsize;
    while (destsize) {
        movesize = (donesize < destsize) ? donesize : destsize;
        memcpy(nextdest, dest, movesize);
        nextdest += movesize; destsize -= movesize; donesize += movesize;
    }
}

void straightLine(int x1,int y1,int x2,CRGB Color)
{
    if (y1<0  or y1>=LED_HEIGHT)
        return;
    if(x1>=LED_WIDTH and x2>=LED_WIDTH)
        return;
    if(x1 <0 and x2<0)
        return;
    if(x1<0)
        x1=0;
    if(x1>=LED_WIDTH)
        x1=LED_WIDTH-1;
    
    
    if(x2<0)
        x2=0;
    if(x2>=LED_WIDTH)
        x2=LED_WIDTH-1;
    
    if(Color != line[0])
    {
        line[0]=Color;
        memfill(line, sizeof(line), sizeof(line[0]));
    }
    int fx=0;
    int longueur=0;
    if(y1%2==0)
    {
        if(x1>x2)
        {
            fx=x2;
            longueur=x1-x2+1;
        }
        else
        {
            fx=x1;
            longueur=x2-x1+1;
        }
        memcpy((char *) leds +(fx+y1*LED_WIDTH)*sizeof(CRGB), line, longueur*sizeof(CRGB));
        
    }
    else
    {
        if(x1>x2)
        {
            fx=x1;
            longueur=x1-x2+1;
        }
        else
        {
            fx=x2;
            longueur=x2-x1+1;
        }
        memcpy((char *) leds +((LED_WIDTH<<1) * ((y1 >>1)  + 1) - 1 - fx)*sizeof(CRGB), line, longueur*sizeof(CRGB));
    }
}


void    glbDrawLine(int firstx,int firsty,int lastx,int lasty,CRGB Color)
{
    int         x1;        /* debut de la ligne => milieu de la ligne */
    int         y1;        /* debut de la ligne => milieu de la ligne */
    int         x2;        /* fin de la ligne => milieu de la ligne */
    int         y2;        /* fin de la ligne => milieu de la ligne */
    int         dx;        /* longueur X de la droite */
    int         dy;        /* longueur Y de la droite */
    int         sub;        /* utilise pour des soustractions */
    int         remain;        /* nombre de pixel restant */
    int         error;        /* erreur du trace, doit etre corrige si positif */
    int         inc1;        /* pour des incrementations/decrementations */
    int         inc2;        /* pour des incrementations/decrementations */
    
    /*
     x1 = premier point X
     x2 = dernier point X
     y1 = premier point Y
     y2 = dernier point Y
     
     si firstx > lastx les premiers et les derniers sont inverses
     
     
     */
    
    if(firsty==lasty)
    {
        straightLine(firstx,firsty,lastx,Color);
        return;
    }
    
     if (firstx>lastx)
     {
     x1=lastx;
     x2=firstx;
     y1=lasty;
     y2=firsty;
     }
     else
     {
     x1=firstx;
     x2=lastx;
     y1=firsty;
     y2=lasty;
     }
     dx=x2-x1;    /* longueur X de la droite */
    dy=y2-y1;    /* longueur Y de la droite */
    if ((!dx)&&(!dy)) return; /* quitte si aucun trace a effectuer */
    
    /*
     si dy negatif, inverse dy et
     initialise les incrementation selon
     le signe de dy (afin que les droites
     aillent dans le bon sens
     
     
     */
     if(y2<y1)

     {
     dy=y1-y2;
     inc1=-1;
     inc2=1;
     }
     else
     {
         dy=y2-y1;
     inc1=1;
     inc2=1;
     }
     
     /*
     pour augmenter la rapidite du code vous pouvez
     rajoutez ici des algos pour les droites
     horizontales (dy==0), verticales (dx==0) et
     diagonale (dx==dy) car ces droites ne necessitent
     pas d'algorythme complique, mais la taille du
     code en souffrira
     
     
     /
     
     
     /*
     pour aller plus vite on dessine la droite des
     deux cotes a la fois, en meme temps a partir
     du premier point et du dernier
     
     
     /
     
     
     /* si la droite est plutot horizontale */
    if (dx>dy)
    {
        sub=dx-dy;
        error=dy-(dx>>1);
        remain=(dx+1)>>1;    /*
                              dx+1 est le nombre de points
                              a tracer, diviser par deux car
                              on dessine des deux cotes a la fois
                              
                              
                              /
                              
                              
                              /*
                              pour mieux comprendre sachez que
                              la position x doit augmenter de 1
                              a chaque tour et y de dy/dx
                              a chaque tour (car sur la longueur
                              dx y doit en tout augmenter de dy).
                              
                              
                              */
                              
                              
                              do
                              {
                             // func(x1,y1);
                                 PixelOn(x1,y1,Color);
                                  /* appelle la fonction de dessin avec en parametre */
        //func(x2,y2);        /* les positions des points a dessiner */
        PixelOn(x2,y2,Color);
        x1+=inc2;    /* la position x1 augmente */
        x2-=inc2;   /* et la position x2 diminue (on va vers le centre) */
        if (error>=0)    /* si l'erreur est assez grande pour etre corrigee */
        {
            y1+=inc1;    /* la position y1 augmente */
            y2-=inc1;    /* et la position y2 diminue (on va vers le centre) */
            error-=sub;    /* diminue l'erreur */
        }
        else error+=dy;    /* sinon augmente l'erreur */
    } while (--remain>0);    /* diminue remain et recommence s'il reste des points a tracer */
    if (!(dx&1)) PixelOn(x1,y1,Color);    /*
                                  si dx etait pair l'algo n'a pas pu tracer le point du milieu
                                  car il a fait une division entiere par deux sur dx pour
                                  connaitre le nombre de points a tracer et a ainsi perdu le 1
                                  
                                  
                                  */
                                  
                                  return;        /* fin de la fonction */
}
else
{
    sub=dy-dx;
    error=dx-(dy>>1);
    remain=(dy+1)>>1;    /*
                          dy+1 est le nombre de points
                          a tracer, diviser par deux car
                          on dessine des deux cotes a la fois
                          
                          
                          /*
                          
                          
                          /*
                          pour mieux comprendre sachez que
                          la position y doit augmenter de 1
                          a chaque tour et x de dx/dy
                          a chaque tour (car sur la longueur
                          dy x doit en tout augmenter de dx).
                          
                          
                          */
                          
                          
                          do
                          {
                          PixelOn(x1,y1,Color);   /* appelle la fonction de dessin avec en parametre */
    PixelOn(x2,y2,Color);        /* les positions des points a dessiner */
    y1+=inc1;    /* la position y1 augmente */
    y2-=inc1;   /* et la position y2 diminue (on va vers le centre) */
    if (error>=0)    /* si l'erreur est assez grande pour etre corrigee */
    {
        x1+=inc2;    /* la position x1 augmente */
        x2-=inc2;    /* et la position x2 diminue (on va vers le centre) */
        error-=sub;    /* diminue l'erreur */
    }
    else error+=dx;    /* sinon augmente l'erreur */
        } while (--remain>0);    /* diminue remain et recommence s'il reste des points a tracer */
if (!(dy&1)) PixelOn(x1,y1,Color);   /*
                              si dy etait pair l'algo n'a pas pu tracer le point du milieu
                              car il a fait une division entiere par deux sur dy pour
                              connaitre le nombre de points a tracer et a ainsi perdu le 1
                              
                              
                             */
                              
                              return;        /* fin de la fonction */
}
}








void    glbDrawLineR(int firstx,int firsty,int lastx,int lasty,CRGB Color)
{
    int         x1;        /* debut de la ligne => milieu de la ligne */
    int         y1;        /* debut de la ligne => milieu de la ligne */
    int         x2;        /* fin de la ligne => milieu de la ligne */
    int         y2;        /* fin de la ligne => milieu de la ligne */
    int         dx;        /* longueur X de la droite */
    int         dy;        /* longueur Y de la droite */
    int         sub;        /* utilise pour des soustractions */
    int         remain;        /* nombre de pixel restant */
    int         error;        /* erreur du trace, doit etre corrige si positif */
    int         inc1;        /* pour des incrementations/decrementations */
    int         inc2;        /* pour des incrementations/decrementations */
    
    /*
     x1 = premier point X
     x2 = dernier point X
     y1 = premier point Y
     y2 = dernier point Y
     
     si firstx > lastx les premiers et les derniers sont inverses
     
     
     */
    
   /* if(firsty==lasty)
    {
        straightLine(firstx,firsty,lastx,Color);
        return;
    }*/
    
    if (firstx>lastx)
    {
        x1=lastx;
        x2=firstx;
        y1=lasty;
        y2=firsty;
    }
    else
    {
        x1=firstx;
        x2=lastx;
        y1=firsty;
        y2=lasty;
    }
    dx=x2-x1;    /* longueur X de la droite */
    dy=y2-y1;    /* longueur Y de la droite */
    if ((!dx)&&(!dy)) return; /* quitte si aucun trace a effectuer */
    
    /*
     si dy negatif, inverse dy et
     initialise les incrementation selon
     le signe de dy (afin que les droites
     aillent dans le bon sens
     
     
     */
    if(y2<y1)
        
    {
        dy=y1-y2;
        inc1=-1;
        inc2=1;
    }
    else
    {
        dy=y2-y1;
        inc1=1;
        inc2=1;
    }
    
    /*
     pour augmenter la rapidite du code vous pouvez
     rajoutez ici des algos pour les droites
     horizontales (dy==0), verticales (dx==0) et
     diagonale (dx==dy) car ces droites ne necessitent
     pas d'algorythme complique, mais la taille du
     code en souffrira
     
     
     /
     
     
     /*
     pour aller plus vite on dessine la droite des
     deux cotes a la fois, en meme temps a partir
     du premier point et du dernier
     
     
     /
     
     
     /* si la droite est plutot horizontale */
    if (dx>dy)
    {
        sub=dx-dy;
        error=dy-(dx>>1);
        remain=(dx+1)>>1;    /*
                              dx+1 est le nombre de points
                              a tracer, diviser par deux car
                              on dessine des deux cotes a la fois
                              
                              
                              /
                              
                              
                              /*
                              pour mieux comprendre sachez que
                              la position x doit augmenter de 1
                              a chaque tour et y de dy/dx
                              a chaque tour (car sur la longueur
                              dx y doit en tout augmenter de dy).
                              
                              
                              */
        
        
        do
        {
            // func(x1,y1);
            pixOnR(x1,y1,Color);
            /* appelle la fonction de dessin avec en parametre */
            //func(x2,y2);        /* les positions des points a dessiner */
            pixOnR(x2,y2,Color);
            x1+=inc2;    /* la position x1 augmente */
            x2-=inc2;   /* et la position x2 diminue (on va vers le centre) */
            if (error>=0)    /* si l'erreur est assez grande pour etre corrigee */
            {
                y1+=inc1;    /* la position y1 augmente */
                y2-=inc1;    /* et la position y2 diminue (on va vers le centre) */
                error-=sub;    /* diminue l'erreur */
            }
            else error+=dy;    /* sinon augmente l'erreur */
        } while (--remain>0);    /* diminue remain et recommence s'il reste des points a tracer */
        if (!(dx&1)) pixOnR(x1,y1,Color);    /*
                                               si dx etait pair l'algo n'a pas pu tracer le point du milieu
                                               car il a fait une division entiere par deux sur dx pour
                                               connaitre le nombre de points a tracer et a ainsi perdu le 1
                                               
                                               
                                               */
        
        return;        /* fin de la fonction */
    }
    else
    {
        sub=dy-dx;
        error=dx-(dy>>1);
        remain=(dy+1)>>1;    /*
                              dy+1 est le nombre de points
                              a tracer, diviser par deux car
                              on dessine des deux cotes a la fois
                              
                              
                              /*
                              
                              
                              /*
                              pour mieux comprendre sachez que
                              la position y doit augmenter de 1
                              a chaque tour et x de dx/dy
                              a chaque tour (car sur la longueur
                              dy x doit en tout augmenter de dx).
                              
                              
                              */
        
        
        do
        {
            pixOnR(x1,y1,Color);   /* appelle la fonction de dessin avec en parametre */
            pixOnR(x2,y2,Color);        /* les positions des points a dessiner */
            y1+=inc1;    /* la position y1 augmente */
            y2-=inc1;   /* et la position y2 diminue (on va vers le centre) */
            if (error>=0)    /* si l'erreur est assez grande pour etre corrigee */
            {
                x1+=inc2;    /* la position x1 augmente */
                x2-=inc2;    /* et la position x2 diminue (on va vers le centre) */
                error-=sub;    /* diminue l'erreur */
            }
            else error+=dx;    /* sinon augmente l'erreur */
        } while (--remain>0);    /* diminue remain et recommence s'il reste des points a tracer */
        if (!(dy&1)) pixOnR(x1,y1,Color);   /*
                                              si dy etait pair l'algo n'a pas pu tracer le point du milieu
                                              car il a fait une division entiere par deux sur dy pour
                                              connaitre le nombre de points a tracer et a ainsi perdu le 1
                                              
                                              
                                              */
        
        return;        /* fin de la fonction */
    }
}









void  BresenhamCircle(int xc,int yc,int r,CRGB Color)
{
   // List<Point> ret = new List<Point>();
    int x,y,p;
    if (r<0)
        return;
    x=0;
    y=r;
    
   
    PixelOn(xc+x,yc-y, Color);
    PixelOn(xc-x,yc-y, Color);
    PixelOn(xc+x,yc+y, Color);
    PixelOn(xc-x,yc+y, Color);
    PixelOn(xc+y,yc-x, Color);
    PixelOn(xc-y,yc-x, Color);
    PixelOn(xc+y,yc+x, Color);
    PixelOn(xc-y,yc+x, Color);
    
    p=3-(2*r);
    
    for(x=0;x<=y;x++)
    {
        if (p<0)
        {
            p=(p+(4*x)+6);
        }
        else
        {
            y=y-1;
            p=p+((4*(x-y)+10));
        }
        
        PixelOn(xc+x,yc-y, Color);
        PixelOn(xc-x,yc-y, Color);
        PixelOn(xc+x,yc+y, Color);
        PixelOn(xc-x,yc+y, Color);
        PixelOn(xc+y,yc-x, Color);
        PixelOn(xc-y,yc-x, Color);
        PixelOn(xc+y,yc+x, Color);
        PixelOn(xc-y,yc+x, Color);
    }
    
}

void  BresenhamCircleFilled(int xc,int yc,int r,CRGB Color)
{
    // List<Point> ret = new List<Point>();
    int x,y,p;
    if (r<0)
        return;
    x=0;
    y=r;
    
    pixOn(xc+x,yc-y);
    
    p=3-(2*r);
    
    for(x=0;x<=y;x++)
    {
        if (p<0)
        {
            p=(p+(4*x)+6);
        }
        else
        {
            y=y-1;
            p=p+((4*(x-y)+10));
        }
        
        glbDrawLine(xc+x,yc+y,xc-x,yc+y, Color);
        glbDrawLine(xc-x,yc-y,xc+x,yc-y, Color);
        glbDrawLine(xc+y,yc-x,xc-y,yc-x, Color);
        glbDrawLine(xc-y,yc+x,xc+y,yc+x, Color);
    }
    
}




void drawCircleFilled(int x, int y, int r,CRGB Color) {
     int i, j;
     int counter;
    if(r<0)
        return;
     i = 0;
     j = r;
     counter = 3 - (r + r);
    
    straightLine(x - r,y,x + r,Color);
    
    while (j > i) {
        
        if (counter < 0) {
             counter = counter + 6 + i + i + i + i;
             i = i + 1;
        } else {
            if ((counter > 0) and (j > i)) {
                 j = j - 1;
                 counter = (counter + 4) - (j + j + j + j);
            }
        }
        
        straightLine(x - i, y + j, x + i,Color);
        straightLine(x - i, y - j, x + i,Color);
        straightLine(x - j, y + i, x + j,Color);
       straightLine(x - j, y - i, x + j,Color);
        
    }
    return;
}

void drawCircle2(int x, int y, int r,CRGB Color) {
    int i, j;
    int counter;
    if(r<0)
        return;
    i = 0;
    j = r;
    counter = 3 - (r + r);
    
   // straightLine(x - r,y,x + r,Color);
    PixelOn(x + r,y, Color);
    PixelOn(x - r,y, Color);
    PixelOn(x ,y-r, Color);
    PixelOn(x ,y+r, Color);
    while (j > i) {
        
        if (counter < 0) {
            counter = counter + 6 + i + i + i + i;
            i = i + 1;
        } else {
            if ((counter > 0) and (j > i)) {
                j = j - 1;
                counter = (counter + 4) - (j + j + j + j);
            }
        }
        PixelOn(x - i,y + j, Color);
        PixelOn(x + i,y + j, Color);
        PixelOn(x - i,y - j, Color);
        PixelOn(x + i,y - j, Color);
        PixelOn(x - j,y + i, Color);
        PixelOn(x + j,y + i, Color);
        PixelOn(x - j,y - i, Color);
        PixelOn(x + j,y - i, Color);
        //straightLine(x - i, y + j, x + i,Color);
        //straightLine(x - i, y - j, x + i,Color);
        //straightLine(x - j, y + i, x + j,Color);
       // straightLine(x - j, y - i, x + j,Color);
        
    }
    return;
}


/*
R:=101;
x:=0;
y:=R;
d:=(-R) div 2;

while x<=y do
begin
plot8(x,y,255,255,55);
if d<=0 then
begin
x:=x+1;
d:=d+x;
end
else
begin
x:=x+1;
y:=y-1;
d:=d+x-y;
end;
end;
*/
void circle (int xc,int yc,int R, CRGB Color)
{
    int x=0;
    int y=R;
    int d=(-R)/2;
    if(R<0)
        return;
    while(x<=y)
    {
       // PixelOn(x+x0,y+y0,Color);
        PixelOn(xc+x,yc-y, Color);
        PixelOn(xc-x,yc-y, Color);
        PixelOn(xc+x,yc+y, Color);
        PixelOn(xc-x,yc+y, Color);
        PixelOn(xc+y,yc-x, Color);
        PixelOn(xc-y,yc-x, Color);
        PixelOn(xc+y,yc+x, Color);
        PixelOn(xc-y,yc+x, Color);
        if(d<=0)
        {
            x++;
            d=d+x;
        }
        else
        {
            x++;
            y--;
            d=d+x-y;
           // d=d-y;
        }
        
    }
    
}
void circleFilled (int xc,int yc,int R, CRGB Color)
{
    int x=0;
    int y=R;
    int d=(-R)/2;
    if(R<0)
        return;
    while(x<=y)
    {
        // PixelOn(x+x0,y+y0,Color);
       //PixelOn(xc+x,yc-y, Color);
        //PixelOn(xc-x,yc-y, Color);
        //PixelOn(xc+x,yc+y, Color);
        //PixelOn(xc-x,yc+y, Color);
        //PixelOn(xc+y,yc-x, Color);
        //PixelOn(xc-y,yc-x, Color);
        //PixelOn(xc+y,yc+x, Color);
       // PixelOn(xc-y,yc+x, Color);
        glbDrawLine(xc+x,yc+y,xc-x,yc+y, Color);
        glbDrawLine(xc-x,yc-y,xc+x,yc-y, Color);
        glbDrawLine(xc+y,yc-x,xc-y,yc-x, Color);
        glbDrawLine(xc-y,yc+x,xc+y,yc+x, Color);
        
        if(d<=0)
        {
            x++;
            d+=x;
        }
        else
        {
            x++;
            y--;
            d=d+x-y;
            // d=d-y;
        }
        
    }
    
}



void drawcircleFilled(int xc, int yc, int radius, CRGB Color)
{
    if (radius<0)
        return;
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);
    
    while (x >= y)
    {
        glbDrawLine(xc+x,yc+y,xc-x,yc+y, Color);
        glbDrawLine(xc-x,yc-y,xc+x,yc-y, Color);
        glbDrawLine(xc+y,yc-x,xc-y,yc-x, Color);
        glbDrawLine(xc-y,yc+x,xc+y,yc+x, Color);
        
        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}



void drawCircle3(int xc, int yc, int radius, CRGB Color)
{
    if (radius<0)
        return;
    int x = radius;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);
    
    while (x >= y)
    {
        PixelOn(xc+x,yc-y, Color);
        PixelOn(xc-x,yc-y, Color);
        PixelOn(xc+x,yc+y, Color);
        PixelOn(xc-x,yc+y, Color);
        PixelOn(xc+y,yc-x, Color);
        PixelOn(xc-y,yc-x, Color);
        PixelOn(xc+y,yc+x, Color);
        PixelOn(xc-y,yc+x, Color);
        
        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}






void dessinePoly(int x0,int y0,float r,float start,int faceNumber,CRGB Color)
{
    if (faceNumber<2)
        return;
    if (r<0)
        return;
    
    int xs,ys,xn,yn,xi,yi;
    
    xs=(int)round((float)r*cos((float)start)+x0);
    ys=(int)round((float)r*sin((float)start)+y0);
    xi=xs;
    yi=ys;
    for(int i=1;i<faceNumber;i++)
    {
        xn=(int)round((float)r*cos((float)start+2*pi*i/faceNumber)+x0);
        yn=(int)round((float)r*sin((float)start+2*pi*i/faceNumber)+y0);
        glbDrawLine(xn,yn,xs,ys,Color);
        xs=xn;
        ys=yn;
    }
    glbDrawLine(xn,yn,xi,yi,Color);
    
}
#endif /* graphicfunction_h */
