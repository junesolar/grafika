//
// Created by zhuyong.joe on 2024/11/23.
//

#ifndef GRAFIKA_TRIANGLE_H
#define GRAFIKA_TRIANGLE_H

#include "BaseShape.h"

class Triangle: public BaseShape {
public:
    Triangle(std::shared_ptr<IFileLoader> fileLoader);
    ~Triangle();
    virtual void draw();
};

#endif //GRAFIKA_TRIANGLE_H
