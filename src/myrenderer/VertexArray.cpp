#include "VertexArray.h"
#include "VertexBuffer.h"

#include <bugl2.h>

namespace myrenderer
{
	VertexArray::VertexArray(std::string path)
	{
		vertCount = buLoadModel(path, &positionsVbo, &texCoordVbo, &normalsVbo);

		glGenVertexArrays(1, &id);
		if (!id) throw std::exception();
		glBindVertexArray(id);
		glBindBuffer(GL_ARRAY_BUFFER, positionsVbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordVbo);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, normalsVbo);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		// We don't want to trigger getId(), which will erase ... 
		dirty = false;
	}

	VertexArray::VertexArray()
	{
		vertCount = 6;
		// Create a new VAO on the GPU and bind it
		glGenVertexArrays(1, &id);

		if (!id)
		{
			throw std::exception();
		}

		// False = Nothing on GPU
		/* True = If you do use it without uploading any vertices,
		you end up uploading no data to the graphics card. */
		dirty = true;
		buffers.resize(20);
	}

	VertexArray::~VertexArray()
	{
		// Clean up
		glDeleteVertexArrays(1, &id);
		glDeleteBuffers(1, &positionsVbo);
		glDeleteBuffers(1, &texCoordVbo);
		glDeleteBuffers(1, &normalsVbo);
	}

	size_t VertexArray::getVertCount()
	{
		return vertCount;
	}

	void VertexArray::setBuffer(int location, std::shared_ptr<VertexBuffer> buffer)
	{
		// Either going to be a 1 or 0. 
		buffers.at(location) = buffer;
	}
	GLuint VertexArray::getId()
	{
		if (dirty)
		{
			glBindVertexArray(id);

			// Bind the position VBO, assign it to position 0 on the bound VAO
			// and flag it to be used
			// Will return the ID and upload it to the graphics card. As and when it is needed. 
			// Keeps it in sync. 
			for (size_t i = 0; i < buffers.size(); i++)
			{
				// If the buffer hasn't been set, skip it. 
				// We only want to set the ones that are valid. 
				if (!buffers.at(i)) continue;

				glBindBuffer(GL_ARRAY_BUFFER, buffers.at(i)->getId());
				glVertexAttribPointer(i, buffers.at(i)->getComponents(), GL_FLOAT, GL_FALSE, 0, (void*)0);
				glEnableVertexAttribArray(i);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			// Resetting the state. 
			glBindVertexArray(0);
			// re-upload
			dirty = false;
		}

		return id;
	}
}