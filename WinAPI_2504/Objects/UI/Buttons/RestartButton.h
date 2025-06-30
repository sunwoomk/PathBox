#pragma once

class RestartButton : public Button 
{
public:
	RestartButton();
	~RestartButton();

	void Update() override;
	void Render() override;
};