#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	int span = 1;
	ofColor color;

	for (int base_x = -240; base_x <= 240; base_x += 160) {

		for (int base_y = -240; base_y <= 240; base_y += 160) {

			auto color_noise_seed_1 = ofRandom(1000);
			auto color_noise_seed_2 = ofRandom(1000);

			for (int x = -55; x < 55; x += span) {

				for (int y = -55; y < 55; y += span) {

					auto noise_value = ofNoise((x + base_x) * 0.005, (y + base_y) * 0.005 + ofGetFrameNum() * 0.01, ofGetFrameNum() * 0.01);

					if (noise_value > 0.45 && noise_value < 0.53) {

						continue;
					}

					auto color_noise_value_1 = ofNoise(color_noise_seed_1, ofGetFrameNum() * 0.001);
					auto color_noise_value_2 = ofNoise(color_noise_seed_2, ofGetFrameNum() * 0.001);

					this->mesh.addVertex(glm::vec3(x + base_x, y + base_y, 0));
					this->mesh.addVertex(glm::vec3(x + span + base_x, y + base_y, 0));
					this->mesh.addVertex(glm::vec3(x + span + base_x, y + span + base_y, 0));
					this->mesh.addVertex(glm::vec3(x + base_x, y + span + base_y, 0));

					this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 4); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
					this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);

					if (noise_value < 0.45) {

						color.setHsb(ofMap(color_noise_value_1, 0, 0.85, 0, 255), 130, 255);
					}
					else {

						color.setHsb(ofMap(color_noise_value_2, 0, 0.85, 0, 255), 130, 255);
					}
					
					for (int i = 0; i < 4; i++) {

						this->mesh.addColor(color);
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	this->mesh.draw();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}