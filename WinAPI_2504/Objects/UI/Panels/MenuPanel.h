#pragma once

class MenuPanel : public Panel
{
public:
	MenuPanel();
	~MenuPanel();

	void Update() override;
	void Render() override;

	void SetButtons() override;
};