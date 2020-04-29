/***

  Olive - Non-Linear Video Editor
  Copyright (C) 2019 Olive Team

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

***/

#ifndef NODEVIEWSCENE_H
#define NODEVIEWSCENE_H

#include <QGraphicsScene>
#include <QTimer>

#include "node/graph.h"
#include "nodeviewedge.h"
#include "nodeviewitem.h"

OLIVE_NAMESPACE_ENTER

class NodeViewScene : public QGraphicsScene
{
  Q_OBJECT
public:
  NodeViewScene(QObject *parent = nullptr);

  void clear();

  void SelectAll();
  void DeselectAll();

  /**
   * @brief Retrieve the graphical widget corresponding to a specific Node
   *
   * In situations where you know what Node you're working with but need the UI object (e.g. for positioning), this
   * static function will retrieve the NodeViewItem (Node UI representation) connected to this Node in a certain
   * QGraphicsScene. This can be called from any other UI object, since it'll have a reference to the QGraphicsScene
   * through QGraphicsItem::scene().
   *
   * If the scene does not contain a widget for this node (usually meaning the node's graph is not the active graph
   * in this view/scene), this function returns nullptr.
   */
  NodeViewItem* NodeToUIObject(Node* n);

  /**
   * @brief Retrieve the graphical widget corresponding to a specific NodeEdge
   *
   * Same as NodeToUIObject() but returns a NodeViewEdge corresponding to a NodeEdgePtr instead.
   */
  NodeViewEdge* EdgeToUIObject(NodeEdgePtr n);

  void SetGraph(NodeGraph* graph);

  QList<Node*> GetSelectedNodes() const;
  QList<NodeViewItem*> GetSelectedItems() const;

  const QHash<Node*, NodeViewItem*>& item_map() const;
  const QHash<NodeEdge*, NodeViewEdge*>& edge_map() const;

  Qt::Orientation GetFlowOrientation() const;

  NodeViewCommon::FlowDirection GetFlowDirection() const;
  void SetFlowDirection(NodeViewCommon::FlowDirection direction);

  /**
   * @brief Automatically reposition the nodes based on their connections
   */
  void ReorganizeFrom(Node* n);

public slots:
  /**
   * @brief Slot when a Node is added to a graph (SetGraph() connects this)
   *
   * This should NEVER be called directly, only connected to a NodeGraph. To add a Node to the NodeGraph
   * use NodeGraph::AddNode().
   */
  void AddNode(Node* node);

  /**
   * @brief Slot when a Node is removed from a graph (SetGraph() connects this)
   *
   * This should NEVER be called directly, only connected to a NodeGraph. To remove a Node from the NodeGraph
   * use NodeGraph::RemoveNode().
   */
  void RemoveNode(Node* node);

  /**
   * @brief Slot when an edge is added to a graph (SetGraph() connects this)
   *
   * This should NEVER be called directly, only connected to a NodeGraph. To add an edge (i.e. connect two node
   * parameters together), use NodeParam::ConnectEdge().
   */
  void AddEdge(NodeEdgePtr edge);

  /**
   * @brief Slot when an edge is removed from a graph (SetGraph() connects this)
   *
   * This should NEVER be called directly, only connected to a NodeGraph. To remove an edge (i.e. disconnect two node
   * parameters), use NodeParam::DisconnectEdge().
   */
  void RemoveEdge(NodeEdgePtr edge);

private:
  QHash<Node*, NodeViewItem*> item_map_;

  QHash<NodeEdge*, NodeViewEdge*> edge_map_;

  NodeGraph* graph_;

  NodeViewCommon::FlowDirection direction_;

private slots:
  /**
   * @brief Receiver for whenever a node position changes
   */
  void NodePositionChanged(const QPointF& pos);

  /**
   * @brief Receiver for when a node's label has changed
   */
  void NodeLabelChanged();

};

OLIVE_NAMESPACE_EXIT

#endif // NODEVIEWSCENE_H
