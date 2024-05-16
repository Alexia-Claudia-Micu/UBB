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

namespace Lab1
{
    public partial class Form1 : Form
    {
        SqlConnection cs = new SqlConnection("Data Source=YOGA\\SQLEXPRESS;Initial Catalog=Yelp_Reviews;Integrated Security=True;TrustServerCertificate=true;");
        SqlDataAdapter da = new SqlDataAdapter();
        DataSet ds = new DataSet();
        DataSet dAd = new DataSet();
        BindingSource bs = new BindingSource();
        BindingSource bs_child = new BindingSource();


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
            try
            {
                da.SelectCommand = new SqlCommand("SELECT * FROM Business", cs);
                ds.Clear();
                da.Fill(ds);
                parentDataGridView.DataSource = ds.Tables[0];
                bs.DataSource = ds.Tables[0];
            }catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void addButton_Click(object sender, EventArgs e)
        {
            try
            {
                da.InsertCommand = new SqlCommand("INSERT INTO Ad (Buyer, Length) VALUES(@b, @l)", cs);
                da.InsertCommand.Parameters.Add("@b",
           SqlDbType.Int).Value = ds.Tables[0].Rows[bs.Position][0];
                da.InsertCommand.Parameters.Add("@l", SqlDbType.Int).Value =
               Int32.Parse(lengthTextBox.Text);
                cs.Open();
                da.InsertCommand.ExecuteNonQuery();
                MessageBox.Show("Inserted Succesfull to the Database");
                cs.Close();
                // already inserted - apear in the list
                da.Fill(ds);
                parentDataGridView.DataSource = ds.Tables[0];
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                cs.Close();
            }
        }

        private void parentDataGridView_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void parentDataGridView_SelectionChanged(object sender, EventArgs e)
        {
            if (parentDataGridView.SelectedRows.Count > 0)
            {
                // Get the value of the "bid" column from the selected row
                int selectedBid = Convert.ToInt32(parentDataGridView.SelectedRows[0].Cells["bid"].Value);

                da.SelectCommand = new SqlCommand("SELECT * FROM Ad where Buyer = @selectedBid", cs);
                da.SelectCommand.Parameters.Add("@selectedBid",SqlDbType.Int).Value =selectedBid;
                dAd.Clear();
                da.Fill(dAd);
                bs_child.DataSource = dAd.Tables[0];

                // Filter the child DataGridView based on the selected "bid"
                DataView dv = new DataView(dAd.Tables[0]);
                dv.RowFilter = $"Buyer = {selectedBid}";
                childDataGridView.DataSource = dv;

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
            da.UpdateCommand = new SqlCommand("Update Ad set Length = @l where aid = @aid", cs);
            try
            {
                da.UpdateCommand.Parameters.Add("@l",
               SqlDbType.Int).Value = int.Parse(lengthTextBox.Text);
            }catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return;
            }
            da.UpdateCommand.Parameters.Add("@aid",
               SqlDbType.Int).Value = dAd.Tables[0].Rows[bs_child.Position][0];

            cs.Open();
            x = da.UpdateCommand.ExecuteNonQuery();
            cs.Close();
            if (x >= 1)
            {
                MessageBox.Show("The record has been updated");
            }

        }

        private void deleteButton_Click(object sender, EventArgs e)
        {
            DialogResult dr;
            dr = MessageBox.Show("Are you sure?\n No undo afterde lete", "Confirm Deletion", MessageBoxButtons.YesNo);
            if (dr == DialogResult.Yes)
            {
                da.DeleteCommand = new SqlCommand("Delete from Ad where aid = @aid", cs);
               
                da.DeleteCommand.Parameters.Add("@aid",
               SqlDbType.Int).Value = dAd.Tables[0].Rows[bs_child.Position][0];
                cs.Open();
                da.DeleteCommand.ExecuteNonQuery();
                cs.Close();
                ds.Clear();
                da.SelectCommand = new SqlCommand("SELECT * FROM Business", cs);

                da.Fill(ds);
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
    }
}
