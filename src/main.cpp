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
 *  main.cpp
 *
 *  Created by Nader on 29/09/2017.
 */
 

#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <unordered_map>
#include <string>

#include "node.h"
#include "keyPair.h"
#include "sparseGrid.h"

class FuncSystem{
    
public:
    
    double operator()(std::vector<double>& _pos){
        double temp  = 0.0;
        
        
        for(std::vector<double>::iterator it = _pos.begin(); it != _pos.end(); ++it){
            temp += (*it )*(*it )*(*it )*(*it );
            
        }
        temp = 0.5 - temp;
        return (1.0/(std::abs(temp) + 0.1));
    }
    
};

void testNode(){
        sparseGrid<FuncSystem> _grid(2);
        _grid.populateGrid();
    
}


int main(int argc, const char * argv[]) {
    std::cout << "Sparse grid adaptive quadrature method!\n";
    testNode();   
    return 0;
}
