#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <vector>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include "AquaAlien.h"
#include "Explosion.h"
#include "GameObject.h"


GameObject::GameObject(int dx)
    : dx_(dx)
{}


int GameObject::getDx() const
{
    return this->dx_;
}


int & GameObject::setDx()
{
    return this->dx_;
}

// int GameObject::getX() const
// {
//     return this->rect_.x;
// }


// int GameObject::getY() const
// {
//     return this->rect_.y;
// }


// int GameObject::getW() const
// {
//     return this->rect_.w;
// }


// int GameObject::getH() const
// {
//     return this->rect_.h;
// }


// bool GameObject::alive() const
// {
//     return this->isAlive_;
// }


// // void GameObject::dying(int * score)
// // {
// //     this->state_ = 3;
// //     this->isAlive_ = 0;
// // }


// int GameObject::state() const
// {
//     return this->state_;
// }


// int & GameObject::setX()
// {
//     return this->rect_.x;
// }


// int & GameObject::setY()
// {
//     return this->rect_.y;
// }


// bool & GameObject::setAlive()
// {
//     return this->isAlive_;
// }


// int & GameObject::setState()
// {
//     return this->state_;
// }


// int GameObject::getMemX() const
// {
//     return this->memoryX_;
// }


// int GameObject::getMemY() const
// {
//     return this->memoryY_;
// }


// void GameObject::attack()
// {
//     if (this->state_ == 0)
//     {
//         this->state_ = 1;
//         //this->memoryX_ = this->alienX_;
//         //this->memoryY_ = this->alienY_;
//         this->dy_ = this->speed_ / 2;
//         //this->median_ = this->alienX_;
//     }
// }
