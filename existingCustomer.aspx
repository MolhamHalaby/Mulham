<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="existingCustomer.aspx.cs" Inherits="$safeprojectname$.existingCustomer" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    
    <style>

        body {
            background-color: powderblue;
        }

        h1 {
            color: blue;
            text-align: center;
        }

        form {
            margin: 0 auto;
            width: 200px;
            text-align: start;
        }
 
        #cType {
            position: absolute;
            top: 40%;
            left: 45%;
            right: 55%;
            display: inline-block;
            background-color: green; /* Green */
            text-align: center;
            font-size: 15px;
            padding:10px;
            color: white;         
            border: none;
            cursor: pointer;
        }


        h2 {
            position: absolute;
            top: 50%;
            left: 30%;
            right: 70%;
            display: inline-block;
        }
        
        .choosingItems {
            position: absolute;
            top: 60%;
            left: 40%;
            right: 45%;
            display: inline-block;
        }
      
         #displayButton {
            position: absolute;
            top: 21%;
            left: 58%;
            right: 42%;
            display: inline;
            background-color:aqua;
            text-align: center;
            font-size: 15px;
            padding:5px;
        }
     
      
    </style>
         <form id="form1" runat="server">
    <h1>Welcome To IFactor</h1>
    
        <asp:Label ID="labelId" runat="server">ID:</asp:Label>
        <asp:TextBox ID="TextBox1" runat="server"></asp:TextBox>
             <asp:Label ID="labelName" runat="server">Name:</asp:Label>
        <asp:TextBox Enabled="false" ID="TextBox2" runat="server"></asp:TextBox>
             <asp:Label ID="labelPhone" runat="server">Phone Number:</asp:Label>
        <asp:TextBox Enabled="false" ID="TextBox3" runat="server"></asp:TextBox>

        
        <asp:DropDownList Enabled="false" ID="cType" runat="server" AutoPostBack="True">
            <asp:ListItem Enabled="true" Text="CustomerType" Value="-1"></asp:ListItem> 
            <asp:ListItem Text="business" Value="1"></asp:ListItem>      
            <asp:ListItem Text="private" Value="2"></asp:ListItem>
            </asp:DropDownList>
           
    <h2>ServiceType:</h2>

    <div class="choosingItems">   
             <asp:Label Visible="false" ID="label1" runat="server">Item1</asp:Label>
           <asp:CheckBox Visible="false" id="checkbox1" runat="server" AutoPostBack="True" />
             <asp:Label Visible="false" ID="label2" runat="server">Item2</asp:Label>
            <asp:CheckBox Visible="false" id="checkbox2" runat="server" AutoPostBack="True" />
             <asp:Label Visible="false" ID="label3" runat="server">Item3</asp:Label>
            <asp:CheckBox Visible="false" id="checkbox3" runat="server" AutoPostBack="True" />
             <asp:Label Visible="false" ID="label4" runat="server">Item4</asp:Label>
            <asp:CheckBox Visible="false" id="checkbox4" runat="server" AutoPostBack="True" />
             <asp:Label Visible="false" ID="label5" runat="server">Item5</asp:Label>
            <asp:CheckBox Visible="false" id="checkbox5" runat="server" AutoPostBack="True" />
            <asp:Label Visible="false" ID="label6" runat="server">Item6</asp:Label>
            <asp:CheckBox Visible="false" id="checkbox6" runat="server" AutoPostBack="True" />
    </div>

    <div class="but">
    <asp:Button ID="displayButton" runat="server" Text="display" OnClick="dispBtnclicked"/>
        </div>

    
          </form>
</body>
</html>
