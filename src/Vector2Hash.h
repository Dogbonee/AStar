//
// Created by 101142429 on 4/9/2025.
//

#ifndef VECTOR2HASH_H
#define VECTOR2HASH_H
#include <cstddef>
#include <SFML/System/Vector2.hpp>


class Vector2Hash {

public:
    std::size_t operator()(const sf::Vector2i& vector) const;

};



#endif //VECTOR2HASH_H
