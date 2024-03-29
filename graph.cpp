#include "graph.h"
#include <stdexcept>
#include <iostream>
graph::graph() {
    size = 0;
}

graph::graph(int size) 
    : size(size)
    , fluxes(size, std::vector<int>(size, 0))
    , capacities(size, std::vector<int>(size, 0))
    , vertexs(size, std::vector<bool>(size, false))
    , list_dest(size, std::list<int>())
    , list_orig(size, std::list<int>()) { }

graph::graph(const graph& orig)
    : size(orig.size)
    , fluxes(orig.fluxes)
    , capacities(orig.capacities)
    , vertexs(orig.vertexs)
    , list_dest(orig.list_dest)
    , list_orig(orig.list_orig) { }

void graph::set_value(int id_node, int value) {
    fluxes[id_node][id_node] = value;
}
/**
 * Cambia la capacidad de la arista entre id_node_1 y id_node_2 a capacity.
 * @param id_node_1 Id del nodo 1
 * @param id_node_2 Id del nodo 2
 * @param capacity Nueva capacidad
 */
void graph::set_capacity(int id_node_1, int id_node_2, int capacity) {
    if (vertexs[id_node_1][id_node_2]) {
        capacities[id_node_1][id_node_2] = capacity;
        //std::cout << "Anadiendo capacidad desde " << id_node_1 << " a " << id_node_2 << " con valor " << capacity << std::endl;
    }
    else
        throw std::invalid_argument("No existe esa arista (SET_CAPACITY FUNCTION)");
}
/**
 * Cambia el flujo de la arista entre id_node_1 y id_node_2 a flux.
 * @param id_node_1 Id del nodo 1
 * @param id_node_2 Id del nodo 2
 * @param flux Nuevo flujo
 */
void graph::set_flux(int id_node_1, int id_node_2, int flux) {
    if (vertexs[id_node_1][id_node_2]) {
        fluxes[id_node_1][id_node_2] = flux;
       // std::cout << "Anadiendo flujo desde " << id_node_1 << " a " << id_node_2 << " con valor " << flux << std::endl;
    }
    else
        throw std::invalid_argument("No existe esa arista (SET_FLUX FUNCTION)");
}
/**
 * Devuelve el valor del nodo id_node.
 * @param id_node Id del nodo
 * @return Valor del nodo
 */
int graph::get_value(int id_node) {
    return fluxes[id_node][id_node];
}
/**
 * Devuelve la capacidad de la arista entre id_node_1 y id_node_2.
 * @param id_node_1 Id del nodo 1
 * @param id_node_2 Id del nodo 2
 * @return Capacidad de la arista
 */
int graph::get_capacity(int id_node_1, int id_node_2) {
    if (vertexs[id_node_1][id_node_2])
        return capacities[id_node_1][id_node_2];
    else
        throw std::invalid_argument("No existe esa arista (GET_CAPACITY FUNCTION)");
}
/**
 * Devuelve el flujo de la arista entre id_node_1 y id_node_2.
 * @param id_node_1 Id del nodo 1
 * @param id_node_2 Id del nodo 2
 * @return Flujo de la arista
 */
int graph::get_flux(int id_node_1, int id_node_2) {
    if (vertexs[id_node_1][id_node_2])
        return fluxes[id_node_1][id_node_2];
    else
        throw std::invalid_argument("No existe esa arista (GET_FLUX FUNCTION)");
}

int graph::get_size() {
    return size;
}
bool graph::has_edge(int id_node_1, int id_node_2){
    return vertexs[id_node_1][id_node_2];
}
/**
 * Agrega una arista entre id_node_1 y id_node_2.
 * @param id_node_1 Id del nodo 1
 * @param id_node_2 Id del nodo 2
 */
void graph::add_edge(int id_node_1, int id_node_2) {
    if (id_node_1 == id_node_2)
        throw std::invalid_argument("No pueden haber aristas a si mismo");
    else if (!vertexs[id_node_1][id_node_2]) {
        //std::cout << "Anadiendo arista desde " << id_node_1 << " a " << id_node_2 << std::endl;
        vertexs[id_node_1][id_node_2] = true;
        list_dest[id_node_1].insert(list_dest[id_node_1].end(), id_node_2);
        list_orig[id_node_2].insert(list_orig[id_node_2].end(), id_node_1);
    }
}

int graph::get_num_neighbours(int id_node){
    return list_dest[id_node].size();
}

std::list<int> graph::get_neighbours(int id_node){
    return list_dest[id_node];
}

std::list<int> graph::get_parents(int id_node){
    return list_orig[id_node];
}

