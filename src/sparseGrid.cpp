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
 *  sparseGrid.h
 *
 *  Created by Nader on 29/09/2017.
 */

//
//  sparseGrid.h
//  SparseGrid2
//
//  Created by Nader on 07/02/2018.
//  Copyright © 2018 Nader Ganaba. All rights reserved.
//

#ifndef sparseGrid_h
#define sparseGrid_h

#include <iostream>
#include <vector>
#include <cmath>

#include <sstream>
#include <string>
#include <algorithm>

#include "node.h"
#include "keyPair.h"

template<class System>
class sparseGrid{
private:
    KeyPair key_;
    TreeNode *node_;
    int dims_;
public:
    sparseGrid(int dim):dims_(dim){
        key_.add(1, 1);
        key_.add(1, 1);
        
        node_ = new TreeNode(key_, dims_);
    }
    
    void fillTree(TreeNode* node, int level, int maxLevel){
        if(node == NULL){
            return;
        }
        int dims = node->getDims();
        
        node->setFuncVal<System>();
        if(level < maxLevel){
            for(int i=0 ; i < (dims) ; i++){ //It should be i < 2*dims
                
                KeyPair keyL(*(node->getKey()));
                KeyPair keyR(*(node->getKey()));
                
                keyL.incrementLevel(i);
                keyR.incrementLevel(i);
                
                keyL.addL(i);
                keyR.addR(i);
                
                node->setNode((2*i),new TreeNode(keyL, dims));
                node->setNode((2*i+1),new TreeNode(keyR, dims));
                
                fillTree(node->getNode((2*i)), level + 1, maxLevel);
                fillTree(node->getNode((2*i+1)), level + 1, maxLevel);
                
                
            } //for loop
        }//if
    }

    void Adaptive1D(TreeNode* node, int maxLevel, double tol, int dim, std::vector<double> vals){

        int level = node->getLevel(dim);
        int dims = node->getDims();
        double func_val = node->getFuncVal();
        
        if( fabs(node->getSurplus()) > tol && level < (maxLevel)){

            for(int i= 0; i < dims; i++){
                KeyPair keyL(*(node->getKey()));
                keyL.incrementLevel(i);
                keyL.addL(i);
                
                KeyPair keyR(*(node->getKey()));
                keyR.incrementLevel(i);
                keyR.addR(i);
                std::vector<double> vals_temp(_vals);
                if(node->getNode((2*i)) == NULL ){
                    node->setNode((2*i),new TreeNode(keyL, dims));
                    node->setFuncNode<System>(2*i);
                    fillTree(node->getNode((2*i)), (level ), (level + 1));
                    vals_temp.at(2*i) = func_val;
                }

                std::vector<double> vals_temp2(_vals);
                if(node->getNode((2*i + 1)) == NULL ){

                    node->setNode((2*i + 1),new TreeNode(keyR, dims));
                    node->setFuncNode(2*i + 1);
                    vals_temp2.at(2*i + 1) = func_val;
                    fillTree(node->getNode((2*i + 1)), (level ), (level + 1));
                }
                Adaptive1D(node->getNode((2*i)), maxLevel,  tol,   i,   vals);
                Adaptive1D(node->getNode((2*i+1)),  maxLevel, tol,   i, vals);
            }
        } 
    }
    
    
    
    void Adaptive(TreeNode* node, int maxLevel, double tol, std::vector<double> vals){
        int dims = node->getDims();

        Adaptive1D(node, maxLevel, tol, 1, vals);
        
    }

    
    void hierarc(TreeNode* node, int level, int maxLevel, std::vector<double> vals, int flag){
        if(node == NULL){
            return;
        }
        double temp = 0.0;
        int dims = node->getDims();
        int neighbous = node->getSizeNeighbour();
        double func_val = node->getFuncVal();
        
        if(level < maxLevel){
            
            for(int i=0 ; i < neighbous ; i++){  
                std::vector<double> vals_temp(vals);
                vals_temp.at(i) = func_val;
                hierarc<System>(node->getNode((i)),  level + 1, maxLevel, vals_temp, flag);
               
            }
        }
        int count = 0;
        
        Adaptive(node, maxLevel  +1, 2.2, vals);

        for(std::vector<double>::iterator it = vals.begin(); it != vals.end(); ++it){
            temp += 0.5*(vals.at(count++));
        }
       
        
        temp = -1.0*temp;
        node->updateSurplus(temp);
    }

    void printNode(TreeNode* node){
        if(node == NULL  ){
            return;
        }
        int dims = node->getSizeNeighbour();
        node->printPos();
        for(int i = 0; i < (dims); i++){
            printNode(node->getNode(i));
        }
    }
    
    
    void populateGrid(){
        
        fillTree(node_, 1, 4);
        std::vector<double> vals(4, 1.0/0.6);
        hierarc(node_,1,4, vals,1);

        printNode(node_);
    }
    
    
};

#endif /* sparseGrid_h */
