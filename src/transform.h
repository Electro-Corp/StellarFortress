/*
*/
#ifndef TRANSFORM_H
#define TRANSFORM_H
namespace Transform{
    class Vector2{
        public:
            // The vars are public becuase Vector2::GetX sounds stupid
            float x, y;
            Vector2();
            Vector2(float, float);

            // Operators
            Vector2 operator+(Vector2 other);
    };

    class Transform{
        public:
        Vector2 position, scale;
        float angle;

        // Empty
        Transform();
        // Individial Params
        Transform(float, float, float);
        // Nah
        Transform(Vector2, float);

    };
}
#endif