#include <iostream>
#include "func.cpp"

int main()
{
    Dot dot;
    Circle circle, circle2;
    Square square, square2;

    Dotread(dot);
    Dotshow(dot);

    CircleRead(circle);
    CircleShow(circle);
    CirclePerimetr(circle);
    CircleSquare(circle);

    SquareRead(square);
    SquareShow(square);
    SquarePerimetr(square);
    SquareSquare(square);

    DotInCircle(dot, circle);
    DotInSqare(dot, square);

    DotOnCircle(dot, circle);
    DotOnSqare(dot, square);

    std::cout<< "Enter second circle and square" << std::endl;     

    CircleRead(circle2);
    CircleShow(circle2);
    SquareRead(square2);
    SquareShow(square2);

    CirclesCross(circle,circle2);
    SquaresCross(square,square2);
    SquareAndCircleCross(square,circle);
    CircleInCircle(circle,circle2);
    SquareInSquare(square,square2);
    SquareInCircle(square,circle);
    CircleInSquare(square,circle);
}
