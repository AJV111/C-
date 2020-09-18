/*
 * This file is creted to be used in article series at sudipart.wordpress.com
 */

/*
 --------------- Written By Sudip Ghimrie ----------------
 *** Attorney Idiom in Object Oriented Programming ***

# Objective
    Control The Granualrity of access to the implementation details of class
# Motivation
    A friend decleration in C++ or any other OOP language expose all of the
 implementation details of the class while this is not always what intended.
 Even tough there will be a case where we need to grant only some part of the
 details but the C++ do not provide any way to do so. Friendship in C++ is
 Nothing-or-Everything proposition.

 */

/*
 * Motivation Example.
 * The following code sample show the problem arising..
 */

struct One {
   private:
    void A() {
    }
    void B() {
    }
    void C() {
    }

    friend struct Client1;
    /*
     * Altough I just wanted to give access to function A & B
     * But the friendship don't provide me with the power not to share C
     */
};

struct Client1 {
    void classEverything(One& o) {
        o.A();
        o.B();
        o.C();  // I never expected to call this fucntion.
    }
};

/*
 * Solution
 * The following code sample show the solution for above undesirable access
 */

struct Fixed {
   private:
    void A() {
    }
    void B() {
    }
    void C() {
    }

    friend struct Attorny;
};

struct Attorny {
   private:
    static void callA(Fixed& a) {
        a.A();
    }
    static void callB(Fixed& a) {
        a.B();
    }
    friend struct Client2;
};

struct Client2 {
    /*
     * Now this Client has only access to A() and B() through Attorny::callA()
     * and Attorny::callB() respectivily
     */
};

/*
 * Now our abstraction became more safe and the code itself is more expressive.
 * We can continue the process to grant access to C() by making a seperate and
 * attory and so on.
 *
 * We could have also made the function inline but for now I am just focusing on
 * the main iodiom
 * We need to decleare the classes as friend inside attorny class when we need
 * to give access to more clients
 *
 * Also note that we are making attorny member functions private to prevent the
 * call to callA() & callB() to unintended party(thats what we are playingfor..)
 *
 */

/*
 * Reference:
 * Friendship and the Attorney-Client Idiom (Dr. Dobb’s Journal)
 * http://www.boost.org/doc/libs/1_50_0/libs/iterator/doc/iterator_facade.html#iterator-core-access
 * http://www.boost.org/doc/libs/1_50_0/libs/serialization/doc/serialization.html#member
 * http://drdobbs.com/184402053
 */
