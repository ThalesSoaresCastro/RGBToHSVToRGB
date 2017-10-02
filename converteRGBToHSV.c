#include<stdio.h>
#include<stdlib.h>


void imprimeValores(float v[3], int tam);
float Min(float rgb[3], int tam);
float Max(float rgb[3], int tam);
void converteToHSV(float hsv[3],float rgb[3]);
float absolutoVal(float val);
void converteToRGB(float rgb[3], float hsv[3]);
unsigned long criaHex(float rgb[3]);
void main(){
  float rgb[3], hsv[3], rgb2[3];
  unsigned long hex;
  hsv[3] = (0,0,0);
  rgb2[3] = (0,0,0);
  printf("Digite os valores de RGB: ");
  scanf("%f",&rgb[0]);
  scanf("%f",&rgb[1]);
  scanf("%f",&rgb[2]);

  //converteToHSV(hsv,rgb);

  //printf("Min: %f\n", Min(rgb,3));
  //printf("Max: %f\n", Max(rgb,3));

  printf("\nValores digitados: \n");
  imprimeValores(rgb, 3);


  converteToHSV(hsv,rgb);
  printf("\nValores convertidos para HSV: \n");
  imprimeValores(hsv, 3);

  converteToRGB(rgb2, hsv);
  printf("\nValores HSV convertidos para RGB: \n");
  imprimeValores(rgb2, 3);

  hex = criaHex(rgb2);
  printf("\nCor no formato HEX: #%lu\n", hex );
  printf("\nCor no formato HEX: #%.2X%.2X%.2X \n",rgb[0],rgb[1],rgb[2]);

}


void imprimeValores(float v[3], int tam){
  int i;
  for(i = 0; i < tam; i++){
    printf("%f ", v[i]);
  }

}


float Min(float rgb[3], int tam){
  int i;
  float min;
  min = rgb[0];
  for(i = 0; i < tam; i++){
      if(rgb[i] < min){
        min = rgb[i];
      }
  }
  return min;
}

float Max(float rgb[3], int tam){
  int i;
  float max;
  max = rgb[0];
  for(i = 0; i < tam; i++){
      if(rgb[i] > max){
        max = rgb[i];
      }
  }
  return max;

}
//Função que converte RGB para HSV...
void converteToHSV(float hsv[3],float rgb[3]){
/* hsv[0] = H || hsv[1] = S || hsv[2] = V */
/* rgb[0] = R || rgb[1] = G || rgb[2] = B */
    float min, max;

    min = Min(rgb, 3);
    max = Max(rgb, 3);
//------------------------------------------------------------------------------
    //calculando H
    if(max == rgb[0]){
        if(rgb[2] > rgb[1]){
          hsv[0] = ( (60*((rgb[1] - rgb[2]) / (max-min))) + 360 );
        }
        else{
          hsv[0] = ( 60*((rgb[1] - rgb[2]) / (max-min)));
        }
    }
    if(max == rgb[1]){
        hsv[0] = ( (60*((rgb[2] - rgb[0]) / (max-min))) + 120 );
    }
    if(max == rgb[2]){
        hsv[0] = ( (60*((rgb[0] - rgb[1]) / (max-min))) + 240 );
    }
//------------------------------------------------------------------------------
    //calculando S
    hsv[1] = ((max-min)/max);
//------------------------------------------------------------------------------
   //calculando V
   hsv[2] = max;

}

float absolutoVal(float val){
    if(val >= 0.0){
        return val;
    }
    else return -val;
}


//função que converte HSV para RGB...
void converteToRGB(float rgb[3], float hsv[3]){
  /* hsv[0] = H || hsv[1] = S || hsv[2] = V */
  /* rgb[0] = R || rgb[1] = G || rgb[2] = B */
    float hi,f,p,q,t, valAbsoluto;
    /* Se S == 0  então R == G == B == V*/
    if(hsv[1] == 0){
        rgb[0] = hsv[2];
        rgb[1] = hsv[2];
        rgb[2] = hsv[2];

    }
    /* Sendo S!=0, temos: */
    else{
      valAbsoluto = absolutoVal((hsv[0]/60));
      //hi = (int)(hsv[0]/60) % 6 ;
      hi = (int)valAbsoluto%6;
      f = hsv[0]/60 - hi;
      p = hsv[2]*(1-hsv[1]);
      q = hsv[2]*(1-f*hsv[1]) ;
      t = hsv[2]*(1 -(1-f)*hsv[1]);

      if(hi == 0){
        rgb[0] = hsv[2];
        rgb[1] = t;
        rgb[2] = p;
      }
      if(hi == 1){
        rgb[0] = q;
        rgb[1] = hsv[2];
        rgb[2] = p;
      }
      if(hi == 2){
        rgb[0] = p;
        rgb[1] = hsv[2];
        rgb[2] = t;
      }
      if(hi == 3){
        rgb[0] = p;
        rgb[1] = q;
        rgb[2] = hsv[2];
      }
      if(hi == 4){
        rgb[0] = t;
        rgb[1] = p;
        rgb[2] = hsv[2];
      }
      if(hi == 5){
        rgb[0] = hsv[2];
        rgb[1] = p;
        rgb[2] = q;
      }

    }
}


//Função que converte RGB para HEX
unsigned long criaHex(float rgb[3]){
  return (((int)rgb[0] & 0xff) << 16) + (((int)rgb[1] & 0xff) << 8) + ((int)rgb[2] & 0xff);
}
