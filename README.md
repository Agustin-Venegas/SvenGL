# SvenGL
                                                                                
                                                                                
Tarea 2 de Fundamentos de Computación Gráfica
Nombres: Gabriel Jimenez y Agustín Venegas

Las texturas se cargan con una libreria externa (stb_image.h), como PNGs
(el formato DDS no es compatible en uno de los sistemas)

SE NECESITA FREETYPE2 PARA COMPILAR
Se usa para cargar fuentes
El Makefile buscará en /usr/include/freetype2

Para instalarlo, se puede usar el siguiente comando
sudo apt-get install libfreetype6-dev



Hay 4 tipos de luz:
Ambiental/direccional (rojo, desde arriba a la derecha)
Esferica (los cubitos de colores)
Direccional SpotLight (sale desde la camara, acercar el cubo para apreciar)

Hay dos otros tipos de iluminado, que tienen que ver con la textura cargada
La iluminación difusa del cubo principal viene a partir de la textura, y se mezcla con las luces que le llegan
La componente especular del cubo principal depende del angulo de ataque de las luces con respecto al objeto, y dependen del mapa especular cargado.

La luz del cubo blanco se apaga y prende 4 veces por segundo

Instrucciones:
Usar el Mouse para mover la camara

1, 2 y 3 para cambiar de textura del cubo principal
+ y - en el teclado numerico para escalar el cubo principal (de 0.1x hasta 5x)
8, 4, 6 y 2 en el teclado numerico para mover el cubo principal

P prende y apaga la luz spotlight (acercar el cubo con 2 en el teclado
numerico para ver mejor el efecto)


                                                                                
                                           ........                             
                                   ..................                           
                         .....          ................                        
                     .. .. ..   ..',;,.       ...........                       
                   .   .;;,;,.',looxkdl;'..    ...........                      
                      .;lllllldxkOOOkkkdl;. .. ............                     
                  .. .;lccllldkOOkOkkOkc'..':;..............                    
                  . .;ccllcloxkkOOOOkOkl,..lxl:.............                    
                    .,:ccccloxkOOkOkkOOkxo:;lol,. ..........                    
                      ..';loodkOOOOOOOkOOOx,.:c.   ..........                   
                    .,;. 'dkkkOxollcclcccllloxd:.........  ....                 
                  .....'':dkOkOd. ....',,;:::oOd,......      .                  
                 ,loc;:oxl;:dOOxl:'..,:::lxxdxkd;...                            
                .xo,lkOOOOo.c000OkxodO0xooool:'','..                            
                .;ldkO00Oxc:kK000000000l....,:;cdxxc'....                       
                  .:dO0Od;;dO00K00KKKK0kooookOOOkxooc'.',                       
                   .cod:,lkOOkO0000000OkkkOOOOkxo:;;..                          
                   .;od';kkkkdodkOkOOOOOOOOOkxolc,...                           
                   .,cdc,,'''.,okOOOkkOOOOkxo:;:'...                            
                     .;,'.    .;cokkkkkdoolll:,'..  ...     .                   
                      ...',','.  .:dxxlcl:;;;'....  .::. ....                   
                      .'lxddddocc'..;:;'.''.'....  .:c,.......                  
                       .::'.'':xOx;.'.........   .,:c'  .....                   
                   ...  .''',,,:l:........   ...,:cc,   ..... ..                
                 .....    ........        ..';cccc;..   ..........              
               .........          ....,;;:cclcclc;.    ...............          
               .........      .',,:cclooloddollc'. .   .................        
                ...........   .cdxxxdo:;;:::;,,.  ..   ...................      
                    ....  .  .'.',;;,,,,,,,,:c:,. .    .....................    
        ..             ....  .,,',;;:;:ccccccc'.       .......................  
      .....             ...  .',;::ccccccccc;..     ............................
   .........  ....      ...  .',:cccccccccc;.     ..............................
  .......... ......     ..   .',:ccccccccc;.     ...............................
  ......... .......      .  .,,,:ccccccccc,     ................................
  ...... ..........        ..,,,:cccccccc'     .................................
  ..................       .,,,,;:ccccc,..    ..................................

