#include "doctest.h"
#include "Notebook.hpp"
#include "Direction.hpp"
#include "string"
#include "algorithm"
using namespace ariel;
using namespace std;



string nospaces(string input){
    std::erase(input, ' ');
    std::erase(input, '\t');
    std::erase(input, '\n');
    std::erase(input, '\r');
    return input;
}


TEST_CASE("Read-Good input"){
    Notebook notebook2;
    notebook2.write(0,0,0,Direction::Horizontal,"hello");
    CHECK(nospaces(notebook2.read(0,0,0,Direction::Horizontal,5))==nospaces("hello"));
    CHECK(nospaces(notebook2.read(7,2,5,Direction::Horizontal,5))==nospaces("_____"));
    CHECK(nospaces(notebook2.read(0,0,1,Direction::Horizontal,5))==nospaces("ello_"));
     Notebook nb;
     nb.write(1,0,0,Direction::Horizontal,"I");
     nb.write(1,1,0,Direction::Horizontal,"Hate");
     nb.write(1,2,0,Direction::Horizontal,"Real");
     nb.write(1,3,0,Direction::Horizontal,"Madrid");
     CHECK(nospaces(nb.read(1,0,0,Direction::Vertical,4))==nospaces("IHRM"));
     nb.erase(1,0,0,Direction::Horizontal,5);
     CHECK(nospaces(nb.read(1,0,0,Direction::Horizontal,5))==nospaces("~~~~~"));
     nb.write(10,10,10,Direction::Vertical,"CHAILEVI");
     CHECK(nb.read(10,10,10,Direction::Vertical,8)=="CHAILEVI");
     CHECK(nospaces(nb.read(10,10,10,Direction::Vertical,5))!=nospaces("CHAILEVY"));



     
     







}
TEST_CASE("read & write"){    
    Notebook notebook;
    notebook.write(0,0,0,Direction::Horizontal,"asd");
    notebook.write(50,50,0,Direction::Vertical,"lsd");
    notebook.write(2,2,0,Direction::Horizontal,"barcelona");
    notebook.write(3,3,0,Direction::Horizontal,"messi");
    notebook.write(60,66,0,Direction::Vertical,"ety");
    notebook.write(6,6,0,Direction::Horizontal,"aaa");
    Notebook notebook4;
    notebook4.write(0,0,0,Direction::Horizontal,"liel");
    CHECK(notebook4.read(0,0,0,Direction::Horizontal,4)=="liel");
    CHECK(notebook4.read(0,0,0,Direction::Horizontal,5)=="liel_");
    CHECK(notebook4.read(0,0,1,Direction::Horizontal,3)=="iel");
    CHECK(notebook4.read(0,0,1,Direction::Horizontal,5)=="iel__");
    CHECK(notebook4.read(2,2,2,Direction::Horizontal,4)=="____");

    CHECK(nospaces(notebook.read(0,0,0,Direction::Horizontal,3))==nospaces("asd"));
    CHECK(nospaces(notebook.read(50,50,0,Direction::Vertical,3))==nospaces("lsd"));
    CHECK(nospaces(notebook.read(2,2,0,Direction::Horizontal,9))==nospaces("barcelona"));
    CHECK(nospaces(notebook.read(3,3,0,Direction::Horizontal,5))==nospaces("messi"));
    CHECK(nospaces(notebook.read(60,66,0,Direction::Vertical,3))==nospaces("ety"));
    CHECK(nospaces(notebook.read(6,6,0,Direction::Horizontal,3))==nospaces("a                aa"));

    
}
TEST_CASE("erase "){
    Notebook notebook3;
        notebook3.write(0,0,0,Direction::Horizontal,"qwer");
        notebook3.erase(0,0,0,Direction::Horizontal,1);
        CHECK(nospaces(notebook3.read(0,0,0,Direction::Horizontal,4))==nospaces("~wer"));
        notebook3.erase(0,0,0,Direction::Horizontal,2);
        CHECK(nospaces(notebook3.read(0,0,0,Direction::Horizontal,4))==nospaces("~~er"));
        CHECK_THROWS(notebook3.write(0,0,0,Direction::Horizontal,"no"));
        notebook3.erase(0,0,4,Direction::Horizontal,4);
        CHECK(nospaces(notebook3.read(0,0,0,Direction::Horizontal,4))==nospaces("~~er"));
        
} 

TEST_CASE("BAD"){
   Notebook notebook5;
   CHECK(nospaces(notebook5.read(0,0,0,Direction::Horizontal,3))!=nospaces("asd"));
   CHECK_THROWS(notebook5.write(10,10,98,Direction::Horizontal,"holla"));
   notebook5.write(6,6,6,Direction::Horizontal,"waa");
   notebook5.erase(6,6,6,Direction::Horizontal,3);
   CHECK_THROWS(notebook5.write(6,6,6,Direction::Horizontal,"yes"));

   
}













