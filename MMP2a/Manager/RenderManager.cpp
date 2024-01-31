#include "stdafx.h"
#include "RenderManager.h"
#include <algorithm>
#include "InputManager.h"
#include <iostream>

bool compareByLayerNr(const std::shared_ptr<RenderCP>& a, const std::shared_ptr<RenderCP>& b);

void RenderManager::render()
{
	std::sort(layersToRender.begin(), layersToRender.end(), compareByLayerNr);

	for (auto& comp : layersToRender)
	{
		if (comp->getComponentId().find("Enemy") != std::string::npos)
		{
			int a = 0;
		}
		comp->draw();
		std::cout << comp->getComponentId() << std::endl;
	}
	layersToRender = newLayersToRender;
}

void RenderManager::addToLayers(std::shared_ptr<RenderCP> renderCP)
{
	layersToRender.push_back(renderCP);
}

bool compareByLayerNr(const std::shared_ptr<RenderCP>& a, const std::shared_ptr<RenderCP>& b) {
	return a->getLayerNr() < b->getLayerNr();
}

void RenderManager::resetLayers(std::vector<std::shared_ptr<RenderCP>> newLayersToRender) 
{
	layersToRender = newLayersToRender;
}