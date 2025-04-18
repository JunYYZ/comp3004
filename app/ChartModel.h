
// ChartModel.h
#ifndef CHARTMODEL_H
#define CHARTMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QPair>

/**
 * @brief Provides time-series data (time, glucose) for plotting.
 */
class ChartModel : public QAbstractTableModel {
    Q_OBJECT
public:
    void setData(const QVector<QPair<int,double>>& data);
    int rowCount(const QModelIndex &parent = {}) const override;
    int columnCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    QVector<QPair<int,double>> m_data;  // (simMinute, glucose)
};
#endif // CHARTMODEL_H
