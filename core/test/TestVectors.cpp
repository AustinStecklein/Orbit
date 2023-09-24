#define CATCH_CONFIG_MAIN
#include "src/Vector3D.h"
#include "catch.hpp"

using namespace OrbitMath;

TEST_CASE("Vector3D contructors", "[vector3D]")
{
    SECTION("Empty vector")
    {
        Vector3D vector;
        REQUIRE(vector.x == 0);
        REQUIRE(vector.y == 0);
        REQUIRE(vector.z == 0);
    }

     SECTION("fiiled vector")
    {
        Vector3D vector(5.1234, 7.14124, 1.1251E12);
        REQUIRE(vector.x == 5.1234);
        REQUIRE(vector.y == 7.14124);
        REQUIRE(vector.z == 1.1251E12);
    }
}

TEST_CASE("Vector3D operator overloads", "[vector3D]")
{
    Vector3D vector(5.1234, 7.14124, 1.1251E12);

    SECTION("assign")
    {
        Vector3D vector2(7, 12, 112.12412);
        vector = vector2;
        REQUIRE(vector.x == (7));
        REQUIRE(vector.y == (12));
        REQUIRE(vector.z == (112.12412));

    }

    SECTION("addtion")
    {
        Vector3D vector2(7, 12, 112.12412);
        vector += vector2;
        REQUIRE(vector.x == (5.1234 + 7));
        REQUIRE(vector.y == (7.14124 + 12));
        REQUIRE(vector.z == (1.1251E12 + 112.12412));

        Vector3D vector3 = vector2 + vector2;
        REQUIRE(vector3.x == (7 + 7));
        REQUIRE(vector3.y == (12 + 12));
        REQUIRE(vector3.z == (112.12412 + 112.12412));
        REQUIRE(vector2.x == (7));
        REQUIRE(vector2.y == (12));
        REQUIRE(vector2.z == (112.12412));
    }

    SECTION("subtraction")
    {
        Vector3D vector2(7, 12, 112.12412);
        vector -= vector2;
        REQUIRE(vector.x == (5.1234 - 7));
        REQUIRE(vector.y == (7.14124 - 12));
        REQUIRE(vector.z == (1.1251E12 - 112.12412));

        Vector3D vector3 = vector2 - vector2;
        REQUIRE(vector3.x == (7 - 7));
        REQUIRE(vector3.y == (12 - 12));
        REQUIRE(vector3.z == (112.12412 - 112.12412));
        REQUIRE(vector2.x == (7 ));
        REQUIRE(vector2.y == (12));
        REQUIRE(vector2.z == (112.12412));
    }

    SECTION("multiplication")
    {
        double scaleFactor = 9;
        vector *= scaleFactor;
        REQUIRE(vector.x == (5.1234 * 9));
        REQUIRE(vector.y == (7.14124 * 9));
        REQUIRE(vector.z == (1.1251E12 * 9));

        Vector3D vector2(7, 12, 112.12412);
        Vector3D vector3 = vector2 * scaleFactor;
        REQUIRE(vector3.x == (7 * 9));
        REQUIRE(vector3.y == (12 * 9));
        REQUIRE(vector3.z == (112.12412 * 9));
        REQUIRE(vector2.x == (7));
        REQUIRE(vector2.y == (12));
        REQUIRE(vector2.z == (112.12412));
    }

    SECTION("division")
    {
        double scaleFactor = 9;
        vector /= scaleFactor;
        REQUIRE(vector.x == (5.1234 / 9));
        REQUIRE(vector.y == (7.14124 / 9));
        REQUIRE(vector.z == (1.1251E12 / 9));

        Vector3D vector2(7, 12, 112.12412);
        Vector3D vector3 = vector2 / scaleFactor;
        REQUIRE(vector3.x == (7.d / 9.d));
        REQUIRE(vector3.y == (12.d / 9.d));
        REQUIRE(vector3.z == (112.12412d / 9.d));
        REQUIRE(vector2.x == (7.d));
        REQUIRE(vector2.y == (12.d));
        REQUIRE(vector2.z == (112.12412d));
    }

    SECTION("compare")
    {
        Vector3D vector2(5.1234, 7.14124, 1.1251E12);
        REQUIRE(vector == vector2);
        Vector3D vector3(7, 12, 112.12412);
        REQUIRE(vector2 != vector3);
        
    }
}

TEST_CASE("Vector3D math operations", "[vector3D]")
{
    Vector3D vector1(5.1234, 7.14124, 1.1251);
    Vector3D vector2(7.1613, 12.3154, 112.12412);

    SECTION("normalized")
    {
        Vector3D vectorN = vector1.Normalized();
        REQUIRE(vectorN.x == Approx(0.5782147620448284).margin(0.0001).epsilon(1e-12));
        REQUIRE(vectorN.y == Approx(0.8059433944851095).margin(0.0001).epsilon(1e-12));
        REQUIRE(vectorN.z == Approx(0.12697611523141594).margin(0.0001).epsilon(1e-12));
    }

    SECTION("magnitude")
    {
        double vectorMag = vector1.magnitude();
        REQUIRE(vectorMag ==  Approx(8.8607215455d).margin(0.0001).epsilon(1e-12));
    }

    SECTION("distance")
    {
        double vectorDistance = vector1.distance(vector2);
        REQUIRE(vectorDistance == Approx(111.138236).margin(0.0001).epsilon(1e-12));
    }
    SECTION("distanceSquared")
    {
        double vectorDistance2 = vector1.distanceSquared(vector2);
        REQUIRE(vectorDistance2 == Approx(12351.707501191696).margin(0.0001).epsilon(1e-12));
    }
    SECTION("dot")
    {
        double vectorDot = vector1.dot(vector2);
        REQUIRE(vectorDot == Approx(250.788278928d).margin(0.0001).epsilon(1e-12));
    }

    SECTION("cross")
    {
        Vector3D vectorcross = vector1.cross(vector2);
        REQUIRE(vectorcross.x == Approx(786.8491941688).margin(0.0001).epsilon(1e-12));
        REQUIRE((double)vectorcross.y == Approx(-566.399537778d).margin(0.0001).epsilon(1e-12));
        REQUIRE(vectorcross.z == Approx(11.956158348).margin(0.0001).epsilon(1e-12));
    }
    
}
