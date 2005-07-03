#include "precompiled.h"

#include "InputProcessor.h"

#include "ps/Game.h"
#include "graphics/Camera.h"

bool InputProcessor::ProcessInput(GameLoopState* state)
{
	if (! g_Game)
		return false;

	CCamera* camera = g_Game->GetView()->GetCamera();

	CVector3D leftwards = camera->m_Orientation.GetLeft();

	// Calculate a vector pointing forwards, parallel to the ground
	CVector3D forwards = camera->m_Orientation.GetIn();
	forwards.Y = 0.0f;
	if (forwards.GetLength() < 0.001f) // be careful if the camera is looking straight down
		forwards = CVector3D(1.f, 0.f, 0.f);
	else
		forwards.Normalize();

	float l;
	l = forwards.GetLength();
	assert(abs(l - 1.f) < 0.0001f);
	l = leftwards.GetLength();
	assert(abs(l - 1.f) < 0.0001f);


	bool moved = false;

	if (state->input.scrollSpeed[0] != 0.0f)
	{
		camera->m_Orientation.Translate(forwards * (state->input.scrollSpeed[0] * state->frameLength));
		moved = true;
	}

	if (state->input.scrollSpeed[1] != 0.0f)
	{
		camera->m_Orientation.Translate(forwards * (-state->input.scrollSpeed[1] * state->frameLength));
		moved = true;
	}

	if (state->input.scrollSpeed[2] != 0.0f)
	{
		camera->m_Orientation.Translate(leftwards * (state->input.scrollSpeed[2] * state->frameLength));
		moved = true;
	}

	if (state->input.scrollSpeed[3] != 0.0f)
	{
		camera->m_Orientation.Translate(leftwards * (-state->input.scrollSpeed[3] * state->frameLength));
		moved = true;
	}

	return moved;
}
