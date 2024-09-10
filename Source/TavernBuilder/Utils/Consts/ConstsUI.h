#pragma once

const int NewObjBntIniPosX = -560;
const int NewObjBntIniPosY = -350;

const int NewObjBntSizeX = 250;
const int NewObjBntSizeY = 310;

const int NewObjBntDistX = 320;
const int NewObjBntDistY = 350;

const int NewObjImgSizeX = 250;
const int NewObjImgSizeY = 270;

const int NumNewObjBnt = 40;
const int NewObjBntPerRow = 4;

const int NewObjSliderHeight = 800;
const int NewObjSliderWidth = 20;

constexpr auto NewObjUIHeight = NewObjBntDistY * (NumNewObjBnt / NewObjBntPerRow - 2);

const int CategoryBntSizeX = 150;
const int CategoryBntSizeY = 70;

constexpr int CatBntPosX = NewObjBntIniPosX - 50 - CategoryBntSizeX;
const int CatBntPosY = NewObjBntIniPosY;
const int CatBntDisY = 50 + CategoryBntSizeY;