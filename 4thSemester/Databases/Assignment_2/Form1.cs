using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics.Contracts;
using System.Drawing;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.Data.SqlClient;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Configuration;
using static Azure.Core.HttpHeader;

namespace Lab1
{
    public partial class Form1 : Form
    {
        SqlConnection cs;
        SqlDataAdapter da;
        DataSet ds = new DataSet();
        DataSet dAd;
        BindingSource bs = new BindingSource();
        BindingSource bs_child = new BindingSource();
        List<System.Windows.Forms.TextBox> textBoxes;


        public Form1()
        {
            InitializeComponent();
        }


        private void dataGridViewUpdate()
        {
            parentDataGridView.ClearSelection();
            parentDataGridView.Rows[bs.Position].Selected = true;
        }

        private void connectButton_Click(object sender, EventArgs e)
        {
            da = new SqlDataAdapter();
            dAd = new DataSet();

            try
            {
                string con = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
                cs = new SqlConnection(con);
                string select = ConfigurationSettings.AppSettings["select"];
                da.SelectCommand = new SqlCommand(select, cs);
                ds.Clear();
                da.Fill(ds);
                parentDataGridView.DataSource = ds.Tables[0];

                ds.Clear();
                da.Fill(ds);
                bs.DataSource = ds.Tables[0];
            }catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

            textBoxes = new List<System.Windows.Forms.TextBox>();

            List < String > columnNames= new List<string>(ConfigurationManager.AppSettings["ChildColumnNames"].Split(','));
            panel1.Controls.Clear();

            // Add text boxes dynamically to the panel
            int i = 0;
            foreach (string column in columnNames)
            {
                System.Windows.Forms.TextBox textBox = new System.Windows.Forms.TextBox();
                textBox.Name = column;
                textBox.Text = column;
                textBox.Location = new System.Drawing.Point(10, 10 + i * 30); // Adjust position as needed
                panel1.Controls.Add(textBox);
                textBoxes.Add(textBox);
                i++;
            }
        }

        private void addButton_Click(object sender, EventArgs e)
        {
            int x;
            string addQuery = ConfigurationManager.AppSettings["AddQuery"];
            string addQueryIdParameter = ConfigurationManager.AppSettings["AddQueryIdParameter"];
            string foreignKey = ConfigurationManager.AppSettings["ForeignKey"];
            int selectedId = Convert.ToInt32(parentDataGridView.SelectedRows[0].Cells[foreignKey].Value);
            da.InsertCommand = new SqlCommand(addQuery, cs);
            try
            {
                da.InsertCommand.Parameters.Add(addQueryIdParameter, SqlDbType.Int).Value = selectedId;

                List<String> columnNames = new List<string>(ConfigurationManager.AppSettings["ChildColumnNames"].Split(','));
                List<String> columnParameters = new List<string>(ConfigurationManager.AppSettings["ColumnNamesInsertParameters"].Split(','));
                int columnNumber = int.Parse(ConfigurationManager.AppSettings["ChildColumnNumber"]);

                for (int i = 0; i < columnNumber; i++)
                {
                    if (textBoxes[i].Name.Equals(columnNames[i]))
                    {
                        da.InsertCommand.Parameters.AddWithValue(columnParameters[i], textBoxes[i].Text);
                    }

                }
                cs.Open();
                x = da.InsertCommand.ExecuteNonQuery();
                cs.Close();

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return;
            }


            if (x >= 1)
            {
                MessageBox.Show("The record has been created");
            }
        }

        private void parentDataGridView_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void parentDataGridView_SelectionChanged(object sender, EventArgs e)
        {
            if (parentDataGridView.SelectedRows.Count > 0)
            {
                string foreignKey = ConfigurationManager.AppSettings["ForeignKey"];
                int selectedId = Convert.ToInt32(parentDataGridView.SelectedRows[0].Cells[foreignKey].Value);
                string selectParameter = ConfigurationManager.AppSettings["SelectChildTableParameter"];

                try
                {
                    string connectionString = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
                    using (SqlConnection connection = new SqlConnection(connectionString))
                    {
                        string selectCommand = ConfigurationManager.AppSettings["SelectChildTable"];
                        SqlDataAdapter da = new SqlDataAdapter(selectCommand, connection);
                        da.SelectCommand.Parameters.Add(selectParameter, SqlDbType.Int).Value = selectedId;

                        dAd.Clear();
                        da.Fill(dAd);
                        bs_child.DataSource = dAd.Tables[0];

                        DataView dv = new DataView(dAd.Tables[0]);
                        childDataGridView.DataSource = dv;
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void previousButton_Click(object sender, EventArgs e)
        {
            bs.MovePrevious();
            dataGridViewUpdate();
        }

        private void nextButton_Click(object sender, EventArgs e)
        {
            bs.MoveNext();
            dataGridViewUpdate();
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            int x;
            string updateQuery = ConfigurationManager.AppSettings["UpdateQuery"];
            string childId = ConfigurationManager.AppSettings["ChildId"];
            da.UpdateCommand = new SqlCommand(updateQuery, cs);
            try
            {
                da.UpdateCommand.Parameters.Add(childId, SqlDbType.Int).Value = dAd.Tables[0].Rows[bs_child.Position][0];

                List<String> columnNames = new List<string>(ConfigurationManager.AppSettings["ChildColumnNames"].Split(','));
                List<String> columnParameters = new List<string>(ConfigurationManager.AppSettings["ColumnNamesInsertParameters"].Split(','));
                int columnNumber = int.Parse(ConfigurationManager.AppSettings["ChildColumnNumber"]);

                for(int i = 0; i < columnNumber; i++)
                {
                    if (textBoxes[i].Name.Equals(columnNames[i]))
                    {
                        da.UpdateCommand.Parameters.AddWithValue(columnParameters[i], textBoxes[i].Text);
                    }

                }

                cs.Open();
                x = da.UpdateCommand.ExecuteNonQuery();
                cs.Close();

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return;
            }
            if (x >= 1)
            {
                MessageBox.Show("The record has been updated");
            }

        }

        private void deleteButton_Click(object sender, EventArgs e)
        {
            DialogResult dr;
            dr = MessageBox.Show("Are you sure?\n No undo after delete", "Confirm Deletion", MessageBoxButtons.YesNo);
            if (dr == DialogResult.Yes)
            {
                string connectionString = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    string deleteQuery = ConfigurationManager.AppSettings["DeleteQuery"];
                    string deleteQueryParameter = ConfigurationManager.AppSettings["DeleteQueryParameter"];
                    string select = ConfigurationManager.AppSettings["select"];
                    da.DeleteCommand = new SqlCommand(deleteQuery, cs);

                    try
                    {
                        da.DeleteCommand.Parameters.Add(deleteQueryParameter,
                       SqlDbType.Int).Value = dAd.Tables[0].Rows[bs_child.Position][0];
                        cs.Open();
                        da.DeleteCommand.ExecuteNonQuery();
                        cs.Close();
                        ds.Clear();
                        da.SelectCommand = new SqlCommand(select, cs);

                        da.Fill(ds);
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.Message);
                        return;
                    }
                }
                
            }
            else
            {
                MessageBox.Show("Deletion Aborded");
            }

        }

        private void dataGridViewUpdateChild()
        {
            childDataGridView.ClearSelection();
            childDataGridView.Rows[bs_child.Position].Selected = true;
        }

        private void previousChildButton_Click(object sender, EventArgs e)
        {
            bs_child.MovePrevious();
            dataGridViewUpdateChild();
        }

        private void nextChildButton_Click(object sender, EventArgs e)
        {
            bs_child.MoveNext();
            dataGridViewUpdateChild();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
