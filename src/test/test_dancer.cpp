#include <QString>

#include <QDebug>

#include <doctest.h>


SCENARIO("Basic stuff") {
    GIVEN("Default") {
        WHEN("True") {
            THEN("All is well") { CHECK(true); }
        }
    }
}
