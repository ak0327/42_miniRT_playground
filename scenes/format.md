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
 #Plane     point(xyz)           normalized vec[-1,1]                                       RGB[0,255]
 #Cylinder  center(xyz)          normalized vec[-1,1]              diameter    height       RGB[0,255]
 #Corn      center(xyz)          normalized vec[-1,1]              diameter    height       RGB[0,255]

 color options
  normal color    : RGB
  checker texture : RGB  RGB
  image texture   : RGB  image_filepath, bumpmap_filepath
       only image : RGB  image_filepath, null
       only bump  : RGB  null          , bumpmap_filepath

##################################################################
# Rule

light list: A, L, sl
shape list: sp, pl, cy, co
camera    : C

線型リストに突っ込んでいく
フォーマットを満たさないものがあれば、即NG
読み取った後にCが1以外であればNG

normalized vecの入力は難しく、柔軟性を持たせるためにxyz[-1,1]を内部で正規化するようにしたい

数値の範囲を決める
スペースの数は不問、horizontal tabもOK

,が合わなければNG
atof失敗はNG 0..001など


##################################################################
# 方針

<identifier>を判別
A, C, L, sp, pl, cy, co, sl

isspaceで飛ばしながら読み取っていく感じかな

ex. Ambient)
    get_ambient()
        if (get_lightning_ratio() == FAILURE)
            return(FAILURE)
        if (get_rgb() == FAILURE)
            return (FAILURE)
        return (SUCCESS)




A   0.1                                                 255, 255, 255

C   -5.0, 200.0, -600.0    0, -0.2, 1.0     50

L   0,500,-500           1.0                            255,255,255


pl  0, 0, 0              0, 1, 0                        200,200,200  255,255,255
pl  -200,0,200           1,1,-1                         150,150,150  255,255,255
pl  400,0,200            1,0,0.2                        100,100,100  255,255,255

sp  0,50,-150                             50            180,180,180  "./img/1k_earth.ppm", "./img/1k_earth_normal.ppm"


cy  100,50,0            0,1,0.3           50    130     200,200,200   "", "./img/normalmap_example.ppm"

co  -150,20,0           -0.2, 1.0, 0      65    130     200,200,200
