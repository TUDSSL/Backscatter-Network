/*
 * node.c
 *
 * @author: Amjad Yousef Majid
 * @data : 21/Jun/2018
 */

#include "node.h"
static uint8_t node_id = 0;

/**
 * @description set the node id
 * @param       id: it is the id of the node
 ----------------------------------------------------------------------------*/
void set_node_id(uint8_t id)
{
    node_id = id;
}

/**
 * @description get the node id
 * @return      the node id
 ----------------------------------------------------------------------------*/
uint8_t get_node_id()
{
    return node_id;
}

