A   0.2                                        255, 255, 255

C   -50.0, 0, 20    0, 0, 1     70

L   -40,50,00       0.6                         10, 0, 255

sp  0.0, 0.0, 20.6      12.6                    10, 0, 255

pl  0, 0, -10       0, 1, 0                     0, 0, 2255

cy  50, 0, 20.6     0, 0, 1     14.2    21.42   10, 0, 255


co  0, 0, 0         0, 0, 1     14.2    21.42   10, 0, 255

sl   -40,50,00       0.6                         10, 0, 255


 #Ambient   lightning ratio[0,1]                                                            RGB[0,255]
 #Camera    viewpoint(xyz)       normalized orientation vec[-1,1]  FOV[0,180]
 #Light     point(xyz)           light brightness ratio[0,1]                                RGB[0,255]
 #Spotlight Light point(xyz)     light brightness ratio[0,1]       angle[0-90]              RGB[0,255]
 #Sphere    center point(xyz)    diameter    RGB[0,255]
 #Plane     point(xyz)           normalized vec[-1,1],                                      RGB[0,255]
 #Cylinder  center(xyz)          normalized vec[-1,1]              diameter    height       RGB[0,255]
 #Corn      center(xyz)          normalized vec[-1,1]              diameter    height       RGB[0,255]

 color options
  normal color    : RGB
  checker texture : RGB RGB
  image texture   : image_filepath bumpmap_filepath
       only image : image_filepath null
       only bump  : null           bumpmap_filepath

