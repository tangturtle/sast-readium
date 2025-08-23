#include "Views.h"
#include "../command/Commands.h"
#include "../controller/PageController.h"
#include "../model/PageModel.h"

WidgetFactory::WidgetFactory(PageController* controller, QObject* parent)
    : QObject(parent), _controller(controller) {
    _actionMap["next"] = new NextPageCommand(_controller, this);
    _actionMap["prev"] = new PrevPageCommand(_controller, this);
}

QPushButton* WidgetFactory::createButton(const QString& actionID,
                                         const QString& text) {
    if (_actionMap.contains(actionID)) {
        QPushButton* button = new QPushButton(text);
        connect(button, &QPushButton::clicked, _actionMap[actionID],
                &Command::execute);
        return button;
    }
    return nullptr;
}

Viewers::Viewers(WidgetFactory* factory, PageModel* model,
                 PageNavigationDelegate* delegate, QWidget* parent)
    : QWidget(parent), _factory(factory), _model(model), _delegate(delegate) {
    // initUI();
}

// void Viewers::initUI() {
//     QVBoxLayout* layouut = new QVBoxLayout(this);

//     QToolBar* toolbar = new QToolBar(this);

//     QPushButton* nextButton = _factory->createButton("next", "Next");
//     QPushButton* prevButton = _factory->createButton("prev", "Previous");
//     if (nextButton) {
//         toolbar->addWidget(nextButton);
//     }
//     if (prevButton) {
//         toolbar->addWidget(prevButton);
//     }

//     _pageLabel = new QLabel("Page: " +
//     QString::number(_model->currentPage()));

//     connect(_model, &PageModel::pageUpdate, _delegate,
//     &PageNavigationDelegate::viewUpdate);

//     layouut->addWidget(toolbar);
//     layouut->addWidget(_pageLabel);
// }
