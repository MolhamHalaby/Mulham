using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Data.SqlClient;

namespace $safeprojectname$
{
    public partial class existingCustomer : System.Web.UI.Page
    {
       
        protected void Page_Load(object sender, EventArgs e)
        {
             
        }

        protected void dispBtnclicked(object sender, EventArgs e)
        {
            if(TextBox1.Text!="")
            {
                try
                {
                    
                    using (SqlConnection conn = new SqlConnection("Data Source=DESKTOP-QFIHUNJ\\SQLEXPRESS;Initial Catalog=test;Integrated Security=True"))
                    {

                        string insertQuery = "select * from test.dbo.Pratim where customerID=" + TextBox1.Text;
                        conn.Open();
                        using (SqlCommand cmd = new SqlCommand(insertQuery, conn))
                        {
                            SqlDataReader myReader = cmd.ExecuteReader();

 
                            while (myReader.Read()) 
                            { 
                                TextBox2.Text = myReader["customerName"].ToString();
                                TextBox3.Text = myReader["customerPhone"].ToString();
                                cType.Text= myReader["customerType"].ToString();
                                if (cType.SelectedIndex == 1)
                                {

                                    cType.BackColor = System.Drawing.Color.FromName("red");
                                }
                                else
                                {
                                    cType.BackColor = System.Drawing.Color.FromName("blue");
                                }
                            }
                            myReader.Close();
                          
                        }
                        string insertQuery2 = "select * from test.dbo.Sog where customerID=" + TextBox1.Text;
                        using (SqlCommand cmd2 = new SqlCommand(insertQuery2, conn))
                        {
                            SqlDataReader myReader2 = cmd2.ExecuteReader();
                            while (myReader2.Read())
                            {
                               
                                if (myReader2["item"].ToString()==label1.Text)
                                {
                                    checkbox1.Visible = true;
                                    checkbox1.Checked = true;
                                    label1.Visible = true;

                                }
                                if (myReader2["item"].ToString() == label2.Text)
                                {
                                    checkbox2.Visible = true;
                                    checkbox2.Checked = true;
                                    label2.Visible = true;
                                }
                                if (myReader2["item"].ToString() == label3.Text)
                                {
                                    checkbox3.Visible = true;
                                    checkbox3.Checked = true;
                                    label3.Visible = true;
                                }
                                if (myReader2["item"].ToString() == label4.Text)
                                {
                                    checkbox4.Visible = true;
                                    checkbox4.Checked = true;
                                    label4.Visible = true;
                                }
                                if (myReader2["item"].ToString() == label5.Text)
                                {
                                    checkbox5.Visible = true;
                                    checkbox5.Checked = true;
                                    label5.Visible = true;
                                }
                                if (myReader2["item"].ToString() == label6.Text)
                                {
                                    checkbox6.Visible = true;
                                    checkbox6.Checked = true;
                                    label6.Visible = true;
                                }



                            }

                              myReader2.Close();
                        }
                       // conn.Close();
                    }

                }
                catch (Exception ex)
                {
                    Response.Write("error" + ex.ToString());
                }
            }
            else
            {
                ScriptManager.RegisterClientScriptBlock(this, this.GetType(), "alertMessage", "alert('Please,Enter Your ID')", true);
            }
        
        }
    }
}