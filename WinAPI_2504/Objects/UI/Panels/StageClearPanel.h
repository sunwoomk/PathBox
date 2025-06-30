#pragma once

class StageClearPanel : public Panel
{
public:
	StageClearPanel();
	~StageClearPanel();

	void Update() override;
	void Render() override;

	void SetButtons() override;
};
