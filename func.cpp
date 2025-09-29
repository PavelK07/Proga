#include "Structs.h"
#include <math.h>


void Dotread(Dot &dot){
    std::cout<<"enter dot x:";
    std::cin>> dot.x;
    std::cout<<"enter dot y:";
    std::cin>> dot.y;
}   

void Dotshow(Dot &dot){
    std::cout<<"Dot x: "<< dot.x << " y: " << dot.y << std::endl; 
}

void CircleRead(Circle &circle){
    std::cout<<"enter circle center x:";
    std::cin>> circle.center.x;
    std::cout<<"enter circle center y:";
    std::cin>> circle.center.y;
    std::cout<<"enter circle radius:";
    std::cin>> circle.r;
}

void CircleShow(Circle &circle){
    std::cout<< "Circle x: " <<circle.center.x << " y: " << circle.center.y << " radius: " << circle.r << std::endl; 
}

void CircleSquare(Circle &circle){
    std::cout<< "Circle Square: "<< M_PI * circle.r * circle.r << std::endl; 
}

void CirclePerimetr(Circle &circle){
    std::cout<< "Circle Perimetr: "<< 2 * M_PI * circle.r << std::endl; 
}

void SquareRead(Square & square){
    std::cout<<"enter Left High Angle x:";
    std::cin>> square.LeftHighAngle.x;
    std::cout<<"enter Left High Angle y:";
    std::cin>> square.LeftHighAngle.y;
    std::cout<<"enter square sight:";
    std::cin>> square.sight;
}
void SquareShow(Square & square){
    std::cout<< "square left hight angle x: " <<square.LeftHighAngle.x << " y: " << square.LeftHighAngle.y << " , sight: " << square.sight << std::endl; 
}
void SquarePerimetr(Square & square){
    std::cout<< "square Perimetr: "<< square.sight * 4 << std::endl; 
}
void SquareSquare(Square & square){
    std::cout<< "square square: "<< square.sight * square.sight << std::endl; 
}

void DotInCircle(Dot &dot, Circle &circle){
    if (sqrt((dot.x - circle.center.x)*(dot.x - circle.center.x) + (dot.y - circle.center.y)*(dot.y - circle.center.y)) < circle.r){
        std::cout<< "Dot in circle " << std::endl; 
    }else{
        std::cout<< "Dot not in circle " << std::endl; 
    }
}

int DotInCircleInt(Dot &dot, Circle &circle){
    if (sqrt((dot.x - circle.center.x)*(dot.x - circle.center.x) + (dot.y - circle.center.y)*(dot.y - circle.center.y)) < circle.r){
        return 1;
    }else{
        return 0;
    }
}

int DotInOnCircleInt(Dot &dot, Circle &circle){
    if (sqrt((dot.x - circle.center.x)*(dot.x - circle.center.x) + (dot.y - circle.center.y)*(dot.y - circle.center.y)) <= circle.r){
        return 1;
    }else{
        return 0;
    }
}

void DotInSqare(Dot &dot, Square & square){
    if ((square.LeftHighAngle.x < dot.x) and (dot.x < (square.LeftHighAngle.x + square.sight)) and (square.LeftHighAngle.y > dot.y) and (dot.y > (square.LeftHighAngle.y - square.sight))){
        std::cout<< "Dot in square " << std::endl; 
    }else{
        std::cout<< "Dot not in square " << std::endl; 
    }
}

int DotInSqareInt(Dot &dot, Square & square){
    if ((square.LeftHighAngle.x < dot.x) and (dot.x < (square.LeftHighAngle.x + square.sight)) and (square.LeftHighAngle.y > dot.y) and (dot.y > (square.LeftHighAngle.y - square.sight))){
        return 1;
    } else {
        return 0;
    }
}

void DotOnCircle(Dot &dot, Circle &circle){
    if (sqrt((dot.x - circle.center.x)*(dot.x - circle.center.x) + (dot.y - circle.center.y)*(dot.y - circle.center.y)) == circle.r){
        std::cout<< "Dot on circle " << std::endl; 
    }else{
        std::cout<< "Dot not on circle " << std::endl; 
    }
}

void DotOnSqare(Dot &dot, Square & square){
    if ( (((square.LeftHighAngle.x <= dot.x) and (dot.x <= (square.LeftHighAngle.x + square.sight))) and ((dot.y == square.LeftHighAngle.y) or (dot.y == square.LeftHighAngle.y - square.sight)) ) or 
( ((dot.x == square.LeftHighAngle.x) or (dot.x == square.LeftHighAngle.x + square.sight)) and ((square.LeftHighAngle.y >= dot.y) and (dot.y >= (square.LeftHighAngle.y - square.sight))) )  ){
        std::cout<< "Dot on square " << std::endl; 
    }else{
        std::cout<< "Dot not on square " << std::endl; 
    }
}

void CirclesCross(Circle &circle1, Circle &circle2){
    if ( (sqrt((circle1.center.x - circle2.center.x)*(circle1.center.x - circle2.center.x) + (circle1.center.y - circle2.center.y)*(circle1.center.y - circle2.center.y)) < (circle1.r + circle2.r)) and 
    (sqrt((circle1.center.x - circle2.center.x)*(circle1.center.x - circle2.center.x) + (circle1.center.y - circle2.center.y)*(circle1.center.y - circle2.center.y)) >= abs(circle1.r - circle2.r)) ){
        std::cout<< "Circles Crossing " << std::endl; 
    }else{
        std::cout<< "Circles not Crossing " << std::endl; 
    }
}

void SquaresCross(Square & square1, Square & square2){
    Dot LDA1,RHA1,RDA1, LDA2,RHA2,RDA2;   //LeftDounAngle1, RightHightAngle1 ...

    LDA1.x = square1.LeftHighAngle.x;
    LDA1.y = square1.LeftHighAngle.y - square1.sight;
    RHA1.x = square1.LeftHighAngle.x + square1.sight;
    RHA1.y = square1.LeftHighAngle.y;    
    RDA1.x = square1.LeftHighAngle.x+ square1.sight;
    RDA1.y = square1.LeftHighAngle.y - square1.sight;

    LDA2.x = square2.LeftHighAngle.x;
    LDA2.y = square2.LeftHighAngle.y - square1.sight;
    RHA2.x = square2.LeftHighAngle.x + square1.sight;
    RHA2.y = square2.LeftHighAngle.y;    
    RDA2.x = square2.LeftHighAngle.x+ square1.sight;
    RDA2.y = square2.LeftHighAngle.y - square1.sight;
    
    if ( ((DotInSqareInt(LDA1,square2) + DotInSqareInt(RHA1,square2) + DotInSqareInt(RDA1,square2) + DotInSqareInt(square1.LeftHighAngle,square2))<=2) or ((DotInSqareInt(LDA2,square1) + DotInSqareInt(RHA2,square1) + DotInSqareInt(RDA2,square1) + DotInSqareInt(square2.LeftHighAngle,square1))<=2) ){
        std::cout<< "Squares Crossing" << std::endl; 
    } else {
        std::cout<< "Squares not Crossing" << std::endl;
    }
}


void SquareAndCircleCross(Square & square1, Circle & circle1){
    Dot LDA1,RHA1,RDA1;   //LeftDounAngle1, RightHightAngle1 ...

    LDA1.x = square1.LeftHighAngle.x;
    LDA1.y = square1.LeftHighAngle.y - square1.sight;
    RHA1.x = square1.LeftHighAngle.x + square1.sight;
    RHA1.y = square1.LeftHighAngle.y;    
    RDA1.x = square1.LeftHighAngle.x+ square1.sight;
    RDA1.y = square1.LeftHighAngle.y - square1.sight;


    
    if ( DotInOnCircleInt(LDA1,circle1) + DotInOnCircleInt(RHA1,circle1) + DotInOnCircleInt(RDA1,circle1) + DotInOnCircleInt(square1.LeftHighAngle,circle1)<=3){
        std::cout<< "Square and Circle Crossing" << std::endl; 
    } else {
        std::cout<< "Squares and Circle not Crossing" << std::endl;
    }
}

void CircleInCircle(Circle &circle1, Circle &circle2) {
    if ( (circle1.r > circle2.r) and (sqrt((circle1.center.x - circle2.center.x)*(circle1.center.x - circle2.center.x) + (circle1.center.y - circle2.center.y)*(circle1.center.y - circle2.center.y)) < (circle1.r - circle2.r))  )
    {
        std::cout<< "Circle 1 in Circle 2" << std::endl; 
    } else {
        std::cout<< "Circle 1 not in Circle 2" << std::endl;
    }
}

void SquareInSquare(Square & square1, Square & square2){
    Dot LDA1,RHA1,RDA1, LDA2,RHA2,RDA2;   //LeftDounAngle1, RightHightAngle1 ...

    LDA1.x = square1.LeftHighAngle.x;
    LDA1.y = square1.LeftHighAngle.y - square1.sight;
    RHA1.x = square1.LeftHighAngle.x + square1.sight;
    RHA1.y = square1.LeftHighAngle.y;    
    RDA1.x = square1.LeftHighAngle.x+ square1.sight;
    RDA1.y = square1.LeftHighAngle.y - square1.sight;
    
    if ( ((DotInSqareInt(LDA1,square2) + DotInSqareInt(RHA1,square2) + DotInSqareInt(RDA1,square2) + DotInSqareInt(square1.LeftHighAngle,square2))==4) ){
        std::cout<< "Square 1 In Square 2" << std::endl; 
    } else {
        std::cout<< "Square 1 not In Square 2" << std::endl;
    }
}

void SquareInCircle(Square & square1, Circle &circle1) {
    Dot LDA1,RHA1,RDA1, LDA2,RHA2,RDA2;   //LeftDounAngle1, RightHightAngle1 ...

    LDA1.x = square1.LeftHighAngle.x;
    LDA1.y = square1.LeftHighAngle.y - square1.sight;
    RHA1.x = square1.LeftHighAngle.x + square1.sight;
    RHA1.y = square1.LeftHighAngle.y;    
    RDA1.x = square1.LeftHighAngle.x+ square1.sight;
    RDA1.y = square1.LeftHighAngle.y - square1.sight;
    if ( DotInCircleInt(LDA1,circle1) + DotInCircleInt(RHA1,circle1) + DotInCircleInt(RDA1,circle1) + DotInCircleInt(square1.LeftHighAngle,circle1)==4 ) {
        std::cout<< "Square in Circle" << std::endl; 
    } else {
        std::cout<< "Square not in Circle" << std::endl;
    }
}

void CircleInSquare(Square & square1, Circle &circle1) {
    Dot LDA1,RHA1,RDA1,LHA1;   //LeftDounAngle1, RightHightAngle1 ...
    LHA1.x = square1.LeftHighAngle.x + circle1.r;
    LHA1.y = square1.LeftHighAngle.y - circle1.r;
    LDA1.x = square1.LeftHighAngle.x + circle1.r;
    LDA1.y = square1.LeftHighAngle.y - square1.sight + circle1.r;
    RHA1.x = square1.LeftHighAngle.x + square1.sight - circle1.r;
    RHA1.y = square1.LeftHighAngle.y - circle1.r;    
    RDA1.x = square1.LeftHighAngle.x+ square1.sight - circle1.r;
    RDA1.y = square1.LeftHighAngle.y - square1.sight + circle1.r;
    // прибавльем/вычитаем радиус чтобы круг не пересекал квадрат, т.е. центр круга был внутри квадрата, который внутри square1 и стороны которого на расстоянии r от сторон square1  
    if ( DotInCircleInt(LDA1,circle1) + DotInCircleInt(RHA1,circle1) + DotInCircleInt(RDA1,circle1) + DotInCircleInt(LHA1,circle1)==4 ) {
        std::cout<< "Circle  in Square" << std::endl; 
    } else {
        std::cout<< "Circle not in Square" << std::endl;
    }
}



