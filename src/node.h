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
 *  node.h
 *
 *  Created by Nader on 29/09/2017.
 */

#ifndef Node_h
#define Node_h


#include <iostream>
#include <vector>
#include <cmath>

#include <sstream>
#include <string>
#include <algorithm>

#include "keyPair.h"



class TreeNode{
private:
    int _level;
    int _idx;
    KeyPair* _key;
    double func_val;
    double surplus;
    int _dims;
    std::vector<double> _position;
    std::vector<TreeNode*> _neighbours;
    
public:
    TreeNode(){
        func_val = 0.0;
        surplus  = 0.0;
        _key = new KeyPair();
 
    }
    TreeNode(int dims):_dims(dims){
        func_val = 0.0;
        surplus  = 0.0;
        _key = new KeyPair(_dims); 
    }
    
    TreeNode(KeyPair& key){
        func_val = 0.0;
        surplus  = 0.0;
        _key = new KeyPair(key); 
    }
    
    TreeNode(KeyPair& key, int dims):_dims(dims){
        func_val = 0.0;
        surplus  = 0.0;
        _key = new KeyPair(key); 
        for(int i = 0; i < 2*dims; i++){
           // _neighbours.at(i) = NULL;
            _neighbours.push_back(NULL);
        }
        
        setPosition();
    }
    
    void setSurplus(double val){ surplus = val;}
    void updateSurplus(double val) {surplus += val;}
    void setFuncVal(double val){func_val = val;}
    
    
    double getSurplus(){return surplus;}
    double getFuncVal(){return func_val;}
    
    template<typename System>
    void setFuncVal(){
        System func;
        func_val = func(_position);
        surplus = func_val;
    }
    
    template<typename System>
    void setFuncNode(int idx){
        _neighbours.at(idx)->setFuncVal<System>();
    }
    
    
    int getSizeNeighbour(){return _neighbours.size();}
    void printKey(){
        _key->printKey();
    }
    void setNode(int idx, TreeNode* temp){
        _neighbours.at(idx) = temp;
    }
    
    void setNode(TreeNode* temp){
        //_neighbours.pop_back();
        _neighbours.push_back(temp);
    }
    
 
    
    TreeNode* getNode(int idx){
        return _neighbours.at(idx);
    }
 
    
    void setPosition(double val){
        _position.push_back(val);
    }

    
    void setPosition(){
        _position = _key->getPosition();
    }
    void printPos(){
        std::vector<double>::iterator it;
        for(it = _position.begin(); it != _position.end() - 1; ++it){
            std::cout << *it << ", ";
        }
        it = _position.end()-1;
        std::cout << *it; 
        std::cout << ", "  << func_val << ", " << surplus << ", " << fabs(surplus) << ", " << (fabs(surplus) > 3.8) << std::endl;
    }
    
    
    KeyPair* getKey(){
        return _key;
    }
    
    int getIndex(){return _idx;}
    int getLevel(){return _level;}
    int getLevel(int idx){return _key->getLevel(idx);}
    int getDims(){return _dims;}
    
};


#endif /* Node_h */
