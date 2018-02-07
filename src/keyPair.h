/*
 * This code is an implementation of sparse grid adaptive quadrature method.
 * Copyright (C) 2017 Nader Ganaba.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  keyPair.h
 *
 *  Created by Nader on 29/09/2017.
 */

#ifndef KeyPair_h
#define KeyPair_h


#include <iostream>
#include <vector>
#include <cmath>

#include <sstream>
#include <string>
#include <algorithm>

class KeyPair{
private:
    std::vector<int> *_index;
    std::vector<int> *_level;
public:

    KeyPair(){
        _index = new std::vector<int>();
        _level = new std::vector<int>();
    }
    KeyPair(int dims){
        _index = new std::vector<int>(dims);
        _level = new std::vector<int>(dims);
    }
    KeyPair(const KeyPair &key){
        _index = new std::vector<int>();
        _level = new std::vector<int>();
        *_index = *key._index;
        *_level = *key._level;
    }
    
    int& operator[](int idx){return _index->at(idx);}
    
    void addIndex(int idx){
        _index->push_back(idx);
    }
    void addLevel(int idx){
        _level->push_back(idx);
    }
    void resizeLevel(int size, int level){
        _level->clear();
        _level->resize(size, level);
    }
    void addL(int idx){
        _index->at(idx) = 2*(_index->at(idx)) - 1;
    }
    void addR(int idx){
        _index->at(idx) = 2*(_index->at(idx)) + 1;
    }
    void add(int idx, int level){
        _index->push_back(idx);
        _level->push_back(level);
    }
    int getIndex(int idx){
        return _index->at(idx);
    }
    int getLevel(int idx){
        return _level->at(idx);
    }
    void setLevel(int idx, int val){
        _level->at(idx) = val;
    }
    void incrementLevel(int idx){
        _level->at(idx) = _level->at(idx) + 1;
    }
    
    void printKey(){
       int dims = (int) _index->size();
        std::cout << " = [ ";
        for(int i = 0; i < dims - 1; i++){
            std::cout <<_level->at(i)<< ", " <<   _index->at(i) << ", "; //<< std::endl;
        }
        std::cout <<  _level->at(dims - 1) << ", " << _index->at(dims - 1)  << "]";
    }
    
    std::vector<int> getIdx(){
        std::vector<int> _temp;
        int dims = (int) _index->size();
        for(int i = 0; i < dims; i++){
            _temp.push_back(_level->at(i));
            _temp.push_back(_index->at(i));
        }
        return _temp;
    }
    
    std::string getIdxS(){
        
        std::vector<int> _temp;
        int dims = (int) _index->size();
        for(int i = 0; i < dims; i++){
            _temp.push_back(_level->at(i));
            _temp.push_back(_index->at(i));
        }
        
        std::stringstream ss;
        std::copy( _temp.begin(), _temp.end(), std::ostream_iterator<int>(ss, ","));
        std::string s = ss.str();
        s = s.substr(0, s.length()-1);  // get rid of the trailing space
        return s;
        
    }
    
    std::vector<double>& getPosition(){
        int dims = (int) _index->size();
 
        int dims2 = (int) _level->size();
        
        double _coord;
        std::vector<double> *_pos = new std::vector<double>(dims);
        
        for(int i = 0; i < dims; i++){
            _coord = (double) (_index->at(i)) / (pow (2.0, (double)_level->at(i)));
            _pos->at(i) = _coord;
        }
        return *_pos;
    }
};


 

#endif /* KeyPair_h */
