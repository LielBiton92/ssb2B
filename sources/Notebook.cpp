#include "Notebook.hpp"
#include <iostream>
#include "stdexcept"
#include "vector"
#include "string"
using namespace std;
using namespace ariel;
const int col_limit = 100;
 unsigned int i=0;

 void ariel::check_t(const unsigned int col ,const unsigned int tw ){
         if (col + tw  > col_limit){
               throw std::invalid_argument("max col is 100"); 
         }
 }

void ariel::Notebook::check_throws(const unsigned int page ,const unsigned int row ,const unsigned int col ,const Direction state ,const unsigned int numtocheck){
        if(this->check_dirty(page , row , col , state , numtocheck)){
                throw std::invalid_argument("someone else wrote here");
        }
        if (state ==Direction::Horizontal){
                if(col+numtocheck > col_limit){
                throw std::invalid_argument("error ! cannot write after col number 100");
        }
        }
}

void ariel::Notebook::check_pages_size(const unsigned int page ){
        if(mynotebook.size()<=page){
                mynotebook.resize(page+1);
        }
}

bool ariel::Notebook::check_dirty(const unsigned int page ,const unsigned int row ,const unsigned int col ,const Direction state ,const unsigned int numtocheck){
        bool ans = mynotebook.at(page).check_dirty(row , col , state , numtocheck);
        return ans;  
}

void ariel::Notebook::write(const unsigned int page ,const unsigned int row ,const unsigned int col ,const Direction state ,const std::string &towrite){
        check_t(col , towrite.size());
        check_pages_size(page);
        mynotebook[page].write(row , col , state , towrite);
        

}

string ariel::Notebook::read(const unsigned int page ,const  unsigned int row ,const  unsigned int col ,const Direction state ,const unsigned int num){
        if (state == Direction::Horizontal){
                check_t(col , num);
        }
        check_pages_size(page);
      //  this->check_throws(page , row , col , state , num);

        return mynotebook[page].read(row , col , state , num);

}

void ariel::Notebook::erase(const unsigned int page ,const  unsigned int  row ,const  unsigned int col ,const Direction state ,const unsigned int num){

                if (state ==Direction::Horizontal){
                        check_t(col , num);
        }
        check_pages_size(page);
        mynotebook[page].erase(row , col , state , num);
}

void ariel::Notebook::show( unsigned int page){
        check_pages_size(page);
        mynotebook[page].show_page();
}


// ariel::Row::Row(){
//         myrow = (char*)malloc(sizeof(char)*row_limit);
//         for(unsigned long j = 0 ; j < row_limit ; j++){
//                 this->myrow[j]='_';
//         }
// }

ariel::Row::Row(){
        for(unsigned int j = 0 ; j < col_limit ; j++){
                this->myrow.push_back('_');
        }
}
// ariel::Row::~Row(){
//         delete[] myrow;
// }

void ariel::Row::write(const unsigned int pos ,const string &tw){
        for (i = 0;i< tw.size();i++){
                this->myrow[pos+i]=tw[i];
        }
}

void ariel::Row::writechar(const unsigned int pos ,const char tw){
               this->myrow[pos]=tw;   
}

void ariel::Row::erase(const unsigned int pos ,const unsigned int len){
        for (i = 0 ; i< len;i++){
                this->myrow[pos+i]='~';
        }
}

string ariel::Row::read(const unsigned int pos ,const  unsigned int len){
        string ans;
        
        for(i = 0 ; i< len ; i++){
                ans += this->myrow[pos+i];
        }
        return ans;

}





char ariel::Row::readchar(const unsigned int pos){
        return this->myrow[pos];
}

bool ariel::Row::check_dirty(const unsigned int pos ,const unsigned int numtocheck){
        for(i = 0 ; i < numtocheck ; i++){
                if(this->myrow[pos]!='_'){
                        if(this->myrow[pos]=='~'){
                        return true ;
                        }
                        return true ;
                }
                
        }
        return false;
}

bool ariel::Row::check_dirty_char(const unsigned int pos ){
        bool ans = false;
        if(this->myrow[pos]!='_'){
                if(this->myrow[pos]=='~'){
                ans = true;
                return ans;
                }
                return ans;
        }
        return ans;
}

void ariel::Row::show_row(){
         for(unsigned int i = 0 ; i < this->myrow.size(); i++){
                 cout << myrow[i] ;
         }
         cout << endl;
}




void ariel::Page::check_size_rows(const unsigned int row){
        if (this->mypage.size()<=row){
                this->mypage.resize(row+1);       
        }
}


void ariel::Page::check_size_cols(const unsigned int row ,const string &tw){
        if (mypage.size()<=row + tw.size()){
                mypage.resize(row+tw.size());

        }
}
void ariel::Page::check_size_cols_toerase(const unsigned int row ,const unsigned int  numtodel){
        if(mypage.size()<=row+numtodel){
                mypage.resize(row+numtodel);
        }

}

void ariel::Page::write(const unsigned int row ,const  unsigned int pos ,const Direction state ,const std::string &tw){
        check_size_rows(row);
        check_size_cols(row , tw);
        if(check_dirty(row , pos , state , tw.size())){
                throw std::invalid_argument("pleasee");
        }

        if(state == Direction::Horizontal){
                mypage[row].write(pos,tw);
}

        else if(state == Direction::Vertical){
                 unsigned int j = 0;
                 unsigned int k  = row;
                while(k < row+tw.size()){
                        this->mypage[row+j].writechar(pos ,tw.at(j));
                
                        k+=1;
                        j+=1;
                }
        

        }
}

void ariel::Page::erase(const unsigned int row ,const  unsigned int pos ,const Direction state ,const unsigned int numtodel){
        
        if (state == Direction::Horizontal){
                check_size_rows(row);
                mypage[row].erase(pos , numtodel);
        }
        else if (state == Direction::Vertical){
                check_size_cols_toerase(row , numtodel);
                 unsigned int j = 0 ;
                 unsigned int k = row ;
                while(k < row+numtodel){
                        cout << " row: "<< k <<endl;
                        cout << " row+numtodel: "<< row+numtodel <<endl;
                        mypage[row+j].erase(pos , 1);
                        k+=1;
                        j+=1;
                }
                
        }
}

string ariel::Page::read(const unsigned int row ,const  unsigned int pos ,const Direction state ,const  unsigned int numtoread){
        check_size_rows(row);
        check_size_cols_toerase(row , numtoread);
        string res;
        
        if (state == Direction::Horizontal){
                res = mypage[row].read(pos , numtoread);
        }
        else if(state == Direction::Vertical){
                if(mypage.size()<row+numtoread){
                        mypage.resize(row+numtoread);
                }
                 unsigned int j = 0 ; 
                i = row ; 
                while (i < row + numtoread){
                        res += mypage[row+j].readchar(pos);

                        i+= 1;
                        j+= 1;
                        
                        
                }
        }
        return res;
}

bool ariel::Page::check_dirty(const unsigned int row ,const unsigned int pos ,const Direction state ,const unsigned int numtocheck){
        bool ans=false ;
        bool final_ans = false; 
        if( state == Direction::Horizontal){
              ans =   mypage[row].check_dirty(pos , numtocheck);
}

        else if(state == Direction::Vertical){
                check_size_cols_toerase(row , numtocheck);
                unsigned int j = 0;
                unsigned int k  = row;
                while(k < row+numtocheck){
                   ans = this->mypage[row+j].check_dirty_char(pos);
                   if(ans){
                           final_ans = true;
                   }
                        
        
                        k+=1;
                        j+=1;
                }
        

        }
        if (final_ans){
                ans = true;
        }
        return ans;
        
}


void ariel::Page::show_page(){
        for(i = 0 ; i < this->mypage.size(); i++){
                this->mypage.at(i).show_row();
                
        }
        
}











        
        
        


