import std.stdio : writeln;

void main()
{
    // Big numbers can be separated
    // with an underscore "_"
    // to enhance readability.
    int b = 7_000_000;
    short c = cast(short) b; // cast needed
    uint d = b; // fine
    int g;
    assert(g == 0);

    auto f = 3.1415f; // f denotes a float

    // typeid(VAR) returns the type information
    // of an expression.
    writeln("type of f is ", typeid(f));
    double pi = f; // fine
    // for floating-point types
    // implicit down-casting is allowed
    float demoted = pi;

    // access to type properties
    assert(int.init == 0);
    assert(int.sizeof == 4);
    assert(bool.max == 1);
    writeln(int.min, " ", int.max);
    writeln(int.stringof); // int
}