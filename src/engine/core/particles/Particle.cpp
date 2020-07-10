#include "Particle.h"

void particlesTest::init() {
    particleProgram = std::make_shared<ShaderProgram>("particle");

    texture = ResourceLoader::loadTexture("particle.png");

//    int id = 10;
//    float uv_x = (id%8)/8.0f;
//    float uv_y = (id/8)/8.0f;
//    float off = 1.0f/8.0f;
//    float z = -5.0f;
//    float verttices[] = {
//            -1.0f, 1.0f, z, uv_x, 1.0f-uv_y,
//            -1.0f, -1.0f, z, uv_x, 1.0f-(uv_y+off),
//            1.0f, 1.0f, z, uv_x+off, 1.0f-uv_y,
//            1.0f, -1.0f, z, uv_x+off, 1.0f-(uv_y+off),
//    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6*4, nullptr, GL_STREAM_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void*) nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void*) (sizeof(float) * 3));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


//    tempTime = 0.0f;
//
//    float quadVertices[] = { -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
//                             -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
//                             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//                             -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
//                             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//                             1.0f,  1.0f, 0.0f, 1.0f, 1.0f};
//    unsigned int quadVBO;
//    glGenVertexArrays(1, &quadVAO);
//    glGenBuffers(1, &quadVBO);
//    glBindVertexArray(quadVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glBindVertexArray(0);
//
//    ResourceManager::GetShader("particles").use().setInteger("sprite", 0);
//
//    float points[] = { 0.0f,  0.0f, 0.0f};
//    unsigned int billboardVBO;
//    glGenVertexArrays(1, &billboardVAO);
//    glGenBuffers(1, &billboardVBO);
//    glBindVertexArray(billboardVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, billboardVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glBindVertexArray(0);
//
//
//    float positions[] = { -0.2f, -0.2f, 0.2f, -0.2f, 0.2f, 0.2f, -0.2f, 0.2f };
//    float instanted_positions[] = { 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 3.0f, 1.0f, 1.0f, 4.0f, 1.0f };
//    glm::mat4 instanced_matrix[] = { glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f) };
//    float times[] = { 2.0f, 2.0f, 2.0f, 2.0f };
//    std::cout << sizeof(glm::mat4) << std::endl;
//    std::cout << 16*sizeof(float) << std::endl;
//    //glm::mat4 instanced MV[4];
//
//    GLuint offset = 0;
//    glGenVertexArrays(1, &instanceVAO);
//    glGenBuffers(1, &instanceVBO);
//    glBindVertexArray(instanceVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(instanted_positions) + sizeof(instanced_matrix), NULL, GL_STATIC_DRAW);
//    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(positions), positions);
//    offset += sizeof(positions);
//    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(instanted_positions), instanted_positions);
//    offset += sizeof(instanted_positions);
//    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(times), times);
//    offset += sizeof(times);
//    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(instanced_matrix), instanced_matrix);
//    offset += sizeof(instanced_matrix);
//
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)sizeof(positions));
//    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(positions)+sizeof(instanted_positions)));
//    glVertexAttribPointer(3, 16, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(positions)+sizeof(instanted_positions)+sizeof(times)));
//
//    glEnableVertexAttribArray(0);
//    glEnableVertexAttribArray(1);
//    glEnableVertexAttribArray(2);
//    glEnableVertexAttribArray(3);
}

void particlesTest::draw(Mat4 projection, Mat4 view, fVec3 camera) {

    particleProgram->use().setMatrix4("u_proj", projection);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    float fact = (iter%10)/10.0f;
    int id = (iter++)/10;
    particleProgram->set1i("id", id).set1f("factor", fact);
//    std::cout << id << " " << fact << std::endl;

    float uv_x = (id%8)/8.0f;
    float uv_y = (id/8)/8.0f;
    float off = 1.0f/8.0f;
    float z = -5.0f;
    float verttices[] = {
            -1.0f, 1.0f, z, 0, 0, 0,
            -1.0f, -1.0f, z, 0, 0, 0,
            1.0f, 1.0f, z, 0, 0, 0,
            1.0f, -1.0f, z, 0, 0, 0,
    };

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verttices), &verttices[0]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);

//    ResourceManager::GetShader("particles").use().setMatrix4("projection", projection);
//    ResourceManager::GetShader("particles").setMatrix4("view", view);
//    ResourceManager::GetShader("particles").setVector3("cameraPos", camera);
//    glm::mat4 model;
//    model = glm::translate(model, glm::vec3(-2.0f, 1.0f, 4.0f));
//    model[0][0] = view[0][0]; model[1][0] = view[0][1]; model[2][0] = view[0][2];
//    model[0][1] = view[1][0]; model[1][1] = view[1][1]; model[2][1] = view[1][2];
//    model[0][2] = view[2][0]; model[1][2] = view[2][1]; model[2][2] = view[2][2];
//    ResourceManager::GetShader("particles").setMatrix4("model", model);
//
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, ResourceManager::GetTexture("particle.png")->id);
//
//    glBindVertexArray(quadVAO);
//    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 1);
//    glBindVertexArray(0);
//
//    ResourceManager::GetShader("billboard").use().setMatrix4("projection", projection);
//    ResourceManager::GetShader("billboard").setMatrix4("view", view);
//    ResourceManager::GetShader("billboard").setVector3("camera", camera);
//    for(int i  = 0; i < particles.size(); i++) {
//        glm::mat4 billboardModel;
//        billboardModel = glm::translate(billboardModel, glm::vec3(30.0f, 2.0f, 50.0f) + particles[i].getPosition());
//        //billboardModel[0][0] = view[0][0]; billboardModel[1][0] = view[0][1]; billboardModel[2][0] = view[0][2];
//        //billboardModel[0][1] = view[1][0]; billboardModel[1][1] = view[1][1]; billboardModel[2][1] = view[1][2];
//        //billboardModel[0][2] = view[2][0]; billboardModel[1][2] = view[2][1]; billboardModel[2][2] = view[2][2];
//        ResourceManager::GetShader("billboard").setMatrix4("model", billboardModel);
//
//        glBindVertexArray(billboardVAO);
//        glDrawArrays(GL_POINTS, 0, 1);
//        glBindVertexArray(0);
//    }
//
//    ResourceManager::GetShader("instanced").use().setMatrix4("projection", projection);
//    ResourceManager::GetShader("instanced").setMatrix4("view", view);
//    glm::mat4 instancedModel;
//    instancedModel = glm::translate(instancedModel, glm::vec3(-3.0f, 1.0f, -3.0f));
//    ResourceManager::GetShader("instanced").setMatrix4("model", instancedModel);
//
//    glm::mat4 MV = view * instancedModel;
//    ResourceManager::GetShader("instanced").setVector3("cameraRight", glm::vec3(MV[0][0], MV[1][0], MV[2][0]));
//    ResourceManager::GetShader("instanced").setVector3("cameraUp", glm::vec3(MV[0][1], MV[1][1], MV[2][1]));
//    ResourceManager::GetShader("instanced").setVector3("camera", camera);
//
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, ResourceManager::GetTexture("ParticleAtlas.png")->id);
//
//    glBindVertexArray(instanceVAO);
//    glVertexAttribDivisor(0, 0);
//    glVertexAttribDivisor(1, 1);
//    glVertexAttribDivisor(2, 1);
//    glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, 4);
//    glBindVertexArray(0);
}

void particlesTest::update(float dt, fVec3 camera) {
//    time += dt*20;
//    float cos = std::cos(time);
//    float sin = std::sin(time);
//    glm::vec3 pos(glm::normalize(glm::vec3(sin, 0.0f, cos)));
//    if( (int)(time*1000)%10 == 0 )
//        particles.push_back(Particle(pos, 10.0f*glm::vec3(cos/3.0f, 1.0f, sin/3.0f)));
//    for(int i  = 0; i < particles.size(); i++)
//    {
//        particles[i].update(dt);
//    }
//    for(int i  = 0; i < particles.size(); i++)
//    {
//        if(!particles[i].isAlive())
//            particles.erase(particles.begin() + i);
//    }
//
//    float cos2 = 6*glm::cos(time*0.01); cos2 += 3.0f; cos2 = 6;
//    float sin2 = 6*glm::sin(time*0.01f); sin2 += 3.0f; sin2 = 4;
//    float positions[] = { -0.2f, -0.2f, 0.2f, -0.2f, 0.2f, 0.2f, -0.2f, 0.2f };
////    float newPositions[] = { 1.0f + sin2, 1.0f + cos2, 1.0f + cos2,
////                             1.0f - sin2, 4.0f + cos2, 4.0f - sin2,
////                             1.0f + sin2, 7.0f - cos2, 7.0f - cos2,
////                             1.0f - sin2, 10.0f - cos2, 10.0f + sin2 };
//    float newPositions[] = { cos2 * 1.0f, 4.0f, sin2 * 4.0f,
//                             cos2 * 2.0f, 4.0f, sin2 * 3.0f,
//                             cos2 * 3.0f, 4.0f, sin2 * 2.0f,
//                             cos2 * 4.0f, 4.0f, sin2 * 1.0f };
//    glm::mat4 instanced_matrix[] = { glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f) };
//    vector<temporary> vPositions;
//    for(unsigned int i = 0; i < 4; i++)
//    {
//        glm::mat4 m;
//        m = glm::translate(m, glm::vec3(newPositions[(i*3)+0], newPositions[(i*3)+1], newPositions[(i*3)+2]));
//        //m[0][0] = view[0][0]; m[1][0] = view[0][1]; m[2][0] = view[0][2];
//        //m[0][1] = view[1][0]; m[1][1] = view[1][1]; m[2][1] = view[1][2];
//        //m[0][2] = view[2][0]; m[1][2] = view[2][1]; m[2][2] = view[2][2];
//        instanced_matrix[i] = m;
//        temporary t;
//        t.x = newPositions[(i*3)+0];
//        t.y = newPositions[(i*3)+1];
//        t.z = newPositions[(i*3)+2];
//        t.cameradistance = glm::length(camera - glm::vec3(t.x, t.y, t.z));
//        vPositions.push_back(t);
//    }
//
//    std::sort(vPositions.begin(), vPositions.end());
//    for(unsigned int i = 0; i < vPositions.size(); i++)
//    {
//        newPositions[(i*3)+0] = vPositions[i].x;
//        newPositions[(i*3)+1] = vPositions[i].y;
//        newPositions[(i*3)+2] = vPositions[i].z;
//    }
//
//
//    ResourceManager::GetShader("instanced").use().setMatrix4("matricies[0]", instanced_matrix[0]);
//    ResourceManager::GetShader("instanced").setMatrix4("matricies[1]", instanced_matrix[1]);
//    ResourceManager::GetShader("instanced").setMatrix4("matricies[2]", instanced_matrix[2]);
//    ResourceManager::GetShader("instanced").setMatrix4("matricies[3]", instanced_matrix[3]);
//    tempTime += dt * 80.0f;
//    ResourceManager::GetShader("instanced").setFloat("time", tempTime);
//    ResourceManager::GetShader("transparent").use().setFloat("time", tempTime);
//
//    glBindVertexArray(instanceVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
//    glBufferData(GL_ARRAY_BUFFER, 2*4*sizeof(float)+3*4*sizeof(float)+16*4*sizeof(float), NULL, GL_STREAM_DRAW);
//    GLuint offset = 0;
//    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(positions), positions);
//    offset += sizeof(positions);
//    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(newPositions), newPositions);
//    offset += sizeof(newPositions);
//    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(instanced_matrix), instanced_matrix);
//    offset += sizeof(instanced_matrix);
//    glBindVertexArray(0);
}
