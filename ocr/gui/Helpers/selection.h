#ifndef SELECTION_H
#define SELECTION_H

/*
 * Selection structure that holds
 * x, y, width and height property values
 * from text selection on image
 *
 */

#include <QObject>

struct Selection {
    Q_GADGET
public:
    int m_x;
    int m_y;
    int m_w;
    int m_h;
    int m_visible_w;
    int m_visible_h;
    bool m_is_active;
    Q_PROPERTY(int x MEMBER m_x)
    Q_PROPERTY(int y MEMBER m_y)
    Q_PROPERTY(int w MEMBER m_w)
    Q_PROPERTY(int h MEMBER m_h)
    Q_PROPERTY(int visible_w MEMBER m_visible_w)
    Q_PROPERTY(int visible_h MEMBER m_visible_h)
    Q_PROPERTY(bool is_active MEMBER m_is_active)
};

#endif // SELECTION_H
