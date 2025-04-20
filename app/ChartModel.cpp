// ChartModel.cpp
#include "ChartModel.h"
#include <QVariant>

void ChartModel::setData(const QVector<QPair<int,double>>& data) {
    beginResetModel();
    m_data = data;
    endResetModel();
}

int ChartModel::rowCount(const QModelIndex&) const { return m_data.size(); }
int ChartModel::columnCount(const QModelIndex&) const { return 2; }

QVariant ChartModel::data(const QModelIndex &index, int role) const {
    if(role != Qt::DisplayRole) return {};
    auto [t, g] = m_data.at(index.row());
    return index.column()==0 ? QVariant(t) : QVariant(g);
}
