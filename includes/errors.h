#ifndef ERRORS_H
# define ERRORS_H

enum e_errors
{
// RES
resx     =  1,
resy        ,
resless     ,
resmore     ,
resisdef    ,
nores       ,

// AMB
amblum      ,
ambr        ,
ambg        ,
ambb        ,
ambrgbmore  ,
ambrgbles   ,
ambmore     ,
ambless     ,
ambisdef    ,
// CAM
camx        ,
camy        ,
camz        ,
camxyzmore  ,
camxyzless  ,
camnormx    ,
camnormy    ,
camnormz    ,
camnormmore ,
camnormless ,
camzeronorm ,
camfov      ,
cammore     ,
camless     ,
// LSRC
lsx        ,
lsy        ,
lsz        ,
lsxyzmore  ,
lsxyzless  ,
lslum      ,
lsr        ,
lsg        ,
lsb        ,
lsrgbmore  ,
lsrgbless  ,
lsmore     ,
lsless     ,
// PL
plx        ,
ply        ,
plz        ,
plxyzmore  ,
plxyzless  ,
plnormx    ,
plnormy    ,
plnormz    ,
plr        ,
plg        ,
plb        ,
plmore     ,
plless     ,
}
#endif