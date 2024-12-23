#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class DrawingLine {
public:
    vector<vec2> points;
    double lifetime;
    double birthtime;
    double fadeDuration; // ����� ������������ �����

    DrawingLine(const vector<vec2>& pts)
        : points(pts), lifetime(5.0), birthtime(app::getElapsedSeconds()), fadeDuration(2.0) {}
};

class courseApp : public App {
public:
    void mouseDown(MouseEvent event) override;
    void mouseDrag(MouseEvent event) override;
    void mouseUp(MouseEvent event) override;
    void keyDown(KeyEvent event) override;
    void update() override;
    void draw() override;

private:
    vector<DrawingLine> lines;
    vector<vec2> currentLine;
};

void courseApp::keyDown(KeyEvent event)
{
    if (event.getChar() == 'f') {
        setFullScreen(!isFullScreen());
    }
    else if (event.getCode() == KeyEvent::KEY_SPACE) {
        lines.clear();
    }
    else if (event.getCode() == KeyEvent::KEY_ESCAPE) {
        if (isFullScreen())
            setFullScreen(false);
        else
            quit();
    }
}

void courseApp::mouseDown(MouseEvent event) {
    currentLine.clear(); // �������� ����� �����
    currentLine.push_back(event.getPos()); // ��������� ��������� �����
}

void courseApp::mouseDrag(MouseEvent event) {
    if (!currentLine.empty()) {
        currentLine.push_back(event.getPos()); // ��������� ����� �� ����� ��������������
    }
}

void courseApp::mouseUp(MouseEvent event) {
    if (!currentLine.empty()) {
        lines.emplace_back(currentLine); // ��������� �����
        currentLine.clear(); // ������� ������� �����
    }
}

void courseApp::update() {
    auto currentTime = app::getElapsedSeconds();
    lines.erase(remove_if(lines.begin(), lines.end(),
        [&](const DrawingLine& line) {
            return currentTime - line.birthtime > line.lifetime;
        }), lines.end());
}

void courseApp::draw()
{
    gl::clear(Color::gray(0.1f));

    if (!currentLine.empty()) { // ������ ������� �����
        gl::color(1.0f, 0.0f, 0.0f); // ���� �����
        gl::draw(currentLine); // ������ ����� �� ������ ������� �����
    }

    auto currentTime = app::getElapsedSeconds();

    for (const auto& line : lines) {
        if (!line.points.empty()) {
            // ��������� �����, ��������� � ������� �������� �����
            double elapsedTime = currentTime - line.birthtime;

            // ���� ������ ������ ������� ����� �����, �� ������ �
            if (elapsedTime > line.lifetime) {
                continue;
            }

            // ��������� ���������� ����� ��� �����������
            size_t numPointsToShow = line.points.size();

            // ���� ������ ������ ������� ������������, ��������� ���������� ������������ �����
            if (elapsedTime > line.lifetime - line.fadeDuration) {
                double fadeProgress = (elapsedTime - (line.lifetime - line.fadeDuration)) / line.fadeDuration;
                numPointsToShow = static_cast<size_t>(line.points.size() * (1.0 - fadeProgress));
            }

            // ������������ ���������� ������������ �����
            numPointsToShow = min(numPointsToShow, line.points.size());

            gl::color(1.0f, 0.0f, 0.0f);
            gl::draw(vector<vec2>(line.points.begin(), line.points.begin() + numPointsToShow));
        }
    }
}


CINDER_APP(courseApp, RendererGl)
