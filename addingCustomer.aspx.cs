using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Data.SqlClient;
using System.Configuration;
namespace $safeprojectname$
{
    public partial class addingCustomer : System.Web.UI.Page
    {
      
        string id="",name="",phone="",CustomerType="";
        
        protected void Page_Load(object sender, EventArgs e)
        {
            
        }

        protected void exisCusBut(object sender, EventArgs e)
        {
            Server.Transfer("existingCustomer.aspx");
        }
        protected void btnclicked(object sender, EventArgs e)
        {
            string[] items= new string[6]; 
            id = TextBox1.Text;
            name = TextBox2.Text;
            phone = TextBox3.Text;
            CustomerType = cType.Text;
          
            if(checkbox1.Checked)
            {
                items[0] = label1.Text;

            }
            if (checkbox2.Checked)
            {
                items[1] = label2.Text;
            }
            if (checkbox3.Checked)
            {
                items[2] = label3.Text;
            }
            if (checkbox4.Checked)
            {
                items[3] = label4.Text;
            }
            if (checkbox5.Checked)
            {
                items[4] = label5.Text;
            }
            if (checkbox6.Checked)
            {
                items[5] = label6.Text;
            }
            

            try
            {
                //string connectionString = ConfigurationManager.ConnectionStrings["Data Source=DESKTOP-QFIHUNJ;SQLEXPRESS;Initial Catalog=test;Integrated Security=True"].ToString();
                using (SqlConnection conn = new SqlConnection("Data Source=DESKTOP-QFIHUNJ\\SQLEXPRESS;Initial Catalog=test;Integrated Security=True"))
                {

                    string insertQuery = "insert into test.dbo.Pratim(customerID,customerName,customerPhone,customerType)values (@customerID,@customerName,@customerPhone,@customerType)";
                    conn.Open();
                    using (SqlCommand cmd = new SqlCommand(insertQuery, conn))
                    {
                        cmd.Parameters.AddWithValue("@customerID", id);
                        cmd.Parameters.AddWithValue("@customerName", name);
                        cmd.Parameters.AddWithValue("@customerPhone", phone);
                        cmd.Parameters.AddWithValue("@customerType", CustomerType);
                        
                        cmd.ExecuteNonQuery();

                      //  conn.Close();
                    }
                    string insertQuery2 = "insert into test.dbo.Sog(item,customerID)values(@item,@customerID)";
                    using (SqlCommand cmd2 = new SqlCommand(insertQuery2, conn))
                    {
                        foreach (string i in items)
                        {
                            if (i != null)
                            {
                                cmd2.Parameters.AddWithValue("@item", i);
                                cmd2.Parameters.AddWithValue("@customerID", id);
                                
                                cmd2.ExecuteNonQuery();
                               
                                cmd2.Parameters.Clear();
                            }
                            else
                            {
                                Console.WriteLine("No");
                            }
                        }

                        
                       //  conn.Close();
                    }
                    conn.Close();
                }
                ScriptManager.RegisterClientScriptBlock(this, this.GetType(), "alertMessage", "alert('Saving Successfully')", true);
            }
            catch (Exception ex)
            {
                Response.Write("error" + ex.ToString());
            }
        }

        protected void cType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(cType.SelectedIndex==1)
            {
               
                cType.BackColor = System.Drawing.Color.FromName("red");
            }
            else
            {
                cType.BackColor = System.Drawing.Color.FromName("blue");
            }
        }
    }
}