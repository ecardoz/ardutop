/**
* Este archivo está en etapa experimental, su finalidad es utilizar 
* la misma tarea que el código escrito en Python pero usando el lenguaje C++
* para generar un archivo binario nativo del OS y enviar los datos
* por el puerto serial de manera más eficiente
*
* @author: Edgar C. Cardoz 
* @email: ecardoz@idun.com.mx
* @date: 26/12/2014
*
*/

#include <iostream>
#include <stdio.h>
#include <unistd.h>
using namespace std;

int
main()
{
  FILE *file;
  //Opening device file

  char stream [100];
  file = fopen("/dev/ttyACM0", "w");
  while (true)
    {
      //file = fopen("/dev/ttyACM0", "w");
      cout << ">>" << endl;
      cin >> stream;
      //sleep(3);
      fprintf(file, "%s\0", ""); //Writing to the file
      fprintf(file, "%s\0", stream); //Writing to the file
      usleep(100);
      fprintf(file, "%s\n", ""); //Writing to the file
      //sleep(100);
    }
    fclose(file);

}
