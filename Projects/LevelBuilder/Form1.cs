using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;

namespace LevelBuilder
{
    public partial class LevelBuilder : Form
    {
        public LevelBuilder()
        {
            InitializeComponent();
        }

        private void Save_Click(object sender, EventArgs e)
        {
            //Work out level ID
            string[] files = Directory.GetFiles(Directory.GetCurrentDirectory());
            int levelID = 0;
            int count = 0;
            foreach (string file in files)
            {
                if (Path.GetExtension(file) == ".level")
                {
                    levelID = Convert.ToInt32(Path.GetFileNameWithoutExtension(file));
                    count++;
                }
            }
            if (count != 0)
            {
                levelID++;
            }

            //Compile level data
            string[] levelData = { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" };
            levelData[0] = LevelName.Text + "," + ScoreMk1.Text + "," + ScoreMk2.Text + "," + ScoreMk3.Text;
            levelData[1] = Entity1.Text + "," + XPos1.Text + "," + YPos1.Text + "," + Rotation1.Text;
            levelData[2] = Entity2.Text + "," + XPos2.Text + "," + YPos2.Text + "," + Rotation2.Text;
            levelData[3] = Entity3.Text + "," + XPos3.Text + "," + YPos3.Text + "," + Rotation3.Text;
            levelData[4] = Entity4.Text + "," + XPos4.Text + "," + YPos4.Text + "," + Rotation4.Text;
            levelData[5] = Entity5.Text + "," + XPos5.Text + "," + YPos5.Text + "," + Rotation5.Text;
            levelData[6] = Entity6.Text + "," + XPos6.Text + "," + YPos6.Text + "," + Rotation6.Text;
            levelData[7] = Entity7.Text + "," + XPos7.Text + "," + YPos7.Text + "," + Rotation7.Text;
            levelData[8] = Entity8.Text + "," + XPos8.Text + "," + YPos8.Text + "," + Rotation8.Text;
            levelData[9] = Entity9.Text + "," + XPos9.Text + "," + YPos9.Text + "," + Rotation9.Text;
            levelData[10] = Entity10.Text + "," + XPos10.Text + "," + YPos10.Text + "," + Rotation10.Text;
            levelData[11] = Entity11.Text + "," + XPos11.Text + "," + YPos11.Text + "," + Rotation11.Text;
            levelData[12] = Entity12.Text + "," + XPos12.Text + "," + YPos12.Text + "," + Rotation12.Text;
            levelData[13] = Entity13.Text + "," + XPos13.Text + "," + YPos13.Text + "," + Rotation13.Text;
            levelData[14] = Entity14.Text + "," + XPos14.Text + "," + YPos14.Text + "," + Rotation14.Text;
            levelData[15] = Entity15.Text + "," + XPos15.Text + "," + YPos15.Text + "," + Rotation15.Text;
            levelData[16] = Entity16.Text + "," + XPos16.Text + "," + YPos16.Text + "," + Rotation16.Text;
            levelData[17] = Entity17.Text + "," + XPos17.Text + "," + YPos17.Text + "," + Rotation17.Text;
            levelData[18] = Entity18.Text + "," + XPos18.Text + "," + YPos18.Text + "," + Rotation18.Text;
            levelData[19] = Entity19.Text + "," + XPos19.Text + "," + YPos19.Text + "," + Rotation19.Text;
            levelData[20] = Entity20.Text + "," + XPos20.Text + "," + YPos20.Text + "," + Rotation20.Text;
            levelData[21] = Entity21.Text + "," + XPos21.Text + "," + YPos21.Text + "," + Rotation21.Text;
            levelData[22] = Entity22.Text + "," + XPos22.Text + "," + YPos22.Text + "," + Rotation22.Text;
            levelData[23] = Entity23.Text + "," + XPos23.Text + "," + YPos23.Text + "," + Rotation23.Text;
            levelData[24] = Entity24.Text + "," + XPos24.Text + "," + YPos24.Text + "," + Rotation24.Text;
            levelData[25] = Entity25.Text + "," + XPos25.Text + "," + YPos25.Text + "," + Rotation25.Text;

            //Write level file
            File.WriteAllLines(levelID.ToString() + ".level", levelData);

            //Alert about code change
            MessageBox.Show("Level saved.\nGameVar::LEVELS needs to be updated to reflect new level count.", "Saved!", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void EditorMode_Click(object sender, EventArgs e)
        {
            MessageBox.Show("In-game editor mode enabled.", "Success.", MessageBoxButtons.OK, MessageBoxIcon.Information);
            if (!File.Exists("../../level.editor"))
                File.WriteAllText("../../level.editor", "EDITING ENABLED");
        }

        private void UndoEditorMode_Click(object sender, EventArgs e)
        {
            MessageBox.Show("In-game editor mode disabled.", "Success.", MessageBoxButtons.OK, MessageBoxIcon.Information);
            if (File.Exists("../../level.editor"))
                File.Delete("../../level.editor");
        }

        private void StartGame_Click(object sender, EventArgs e)
        {

        }

        private void LevelBuilder_Load(object sender, EventArgs e)
        {
            if (!File.Exists("../../AngryBirds.exe"))
            {
                MessageBox.Show("Please run LevelBuilder from the LEVELS folder.", "Incorrect directory.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                Close();
            }
        }
    }
}
