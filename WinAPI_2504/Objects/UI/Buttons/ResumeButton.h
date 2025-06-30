#pragma once

class ResumeButton : public Button
{
public:
	ResumeButton();
	~ResumeButton();

	void Update() override;
	void Render() override;
};