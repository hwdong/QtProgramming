#include <QtCore>
#include <QtGui>
#include <QtWidgets>

QImage createImageWithFBO()
{
	QSurfaceFormat format;
//	format.setMajorVersion(3);
//	format.setMinorVersion(3);

	QWindow window;
	window.setSurfaceType(QWindow::OpenGLSurface);
	window.setFormat(format);
	window.setGeometry(0, 0, 400, 400);
	window.create();

	QOpenGLContext context;
	context.setFormat(format);
	if (!context.create())
		qFatal("Cannot create the requested OpenGL context!");
	context.makeCurrent(&window);

	const QRect drawRect(0, 0, 400, 400);
	const QSize drawRectSize = drawRect.size();

	QOpenGLFramebufferObjectFormat fboFormat;
	fboFormat.setSamples(16);
	fboFormat.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);

	QOpenGLFramebufferObject fbo(drawRectSize, fboFormat);
	fbo.bind();

	QOpenGLPaintDevice device(drawRectSize);
	QPainter painter;
	painter.begin(&device);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);

	painter.fillRect(drawRect, Qt::blue);

	painter.drawTiledPixmap(drawRect, QPixmap(":/qt-project.org/qmessagebox/images/qtlogo-64.png"));

	painter.setPen(QPen(Qt::green, 5));
	painter.setBrush(Qt::red);
	painter.drawEllipse(0, 100, 400, 200);
	painter.drawEllipse(100, 0, 200, 400);

	painter.setPen(QPen(Qt::white, 0));
	QFont font;
	font.setPointSize(24);
	painter.setFont(font);
	painter.drawText(drawRect, "Hello FBO", QTextOption(Qt::AlignCenter));

	painter.end();

	fbo.release();
	return fbo.toImage();
}

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QImage targetImage = createImageWithFBO();

	QLabel label;
	label.setPixmap(QPixmap::fromImage(targetImage));
	label.show();
	return app.exec();
}



//====================another solution using QOpenGLWidget=====================
//=======render to offline framebuffer==============
//http://stackoverflow.com/questions/31323749/easiest-way-for-offscreen-rendering-with-qopenglwidget
#include <QOpenGLWidget>
#include <QOpenGLFramebufferObject>
class GLWidget : public QOpenGLWidget
{
public:
	GLWidget(QWidget * parent = 0) :QOpenGLWidget(parent){}
	void drawOffscreen()
	{
		//the context should be valid. make sure it is current for painting
		makeCurrent();
		if (!m_isInitialized)
		{
			initializeGL();
			resizeGL(width(), height());
		}
		if (!m_fbo || m_fbo->width() != width() || m_fbo->height() != height())
		{
			//allocate additional? FBO for rendering or resize it if widget size changed
			delete m_fbo;
			QOpenGLFramebufferObjectFormat format;
			format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
			m_fbo = new QOpenGLFramebufferObject(width(), height(), format);
			resizeGL(width(), height());
		}

		//#2 WORKS: bind FBO and render stuff with paintGL() call
		m_fbo->bind();
		paintGL();
		//You could now grab the content of the framebuffer we've rendered to
		QImage image2 = m_fbo->toImage();
		image2.save(QString("fb2.png"));
		m_fbo->release();
		//#2 --------------------------------------------------------------

		//bind default framebuffer again. not sure if this necessary
		//and isn't supposed to use defaultFramebuffer()...
		m_fbo->bindDefault();
		doneCurrent();
	}

	void paintGL()
	{
		//When doing mixed QPainter/OpenGL rendering make sure to use a QOpenGLPaintDevice, otherwise only OpenGL content is visible!
		//I'm not sure why, because according to the docs (http://doc.qt.io/qt-5/topics-graphics.html) this is supposed to be the same...
		QOpenGLPaintDevice fboPaintDev(width(), height());
		QPainter painter(&fboPaintDev);
		painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
		//This is what you'd use (and what would work) if the widget was visible
		//QPainter painter;
		//painter.begin(this);

		//now start OpenGL painting
		painter.beginNativePainting();
		glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0, 1.0, 1.0);
		glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex3f(0.25, 0.25, 0.0);
		glVertex3f(0.75, 0.25, 0.0);
		glVertex3f(0.75, 0.75, 0.0);
		glVertex3f(0.25, 0.75, 0.0);
		glEnd();
		glFlush();
		painter.endNativePainting();

		//draw non-OpenGL stuff with QPainter
		painter.drawText(20, 40, "Foo");
		painter.end();
	}

private:
	bool m_isInitialized = false;
	QOpenGLFramebufferObject *m_fbo = 0;
};

int main_3(int argc, char *argv[])
{

	QApplication a(argc, argv);
	GLWidget w;
	w.show();

	return a.exec();
}
