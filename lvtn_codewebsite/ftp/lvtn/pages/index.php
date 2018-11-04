<?php require("../template-parts/header.php") ?>

        <div id="page-wrapper">
            <div class="row">
                <div class="col-lg-12">
                    <h1 class="page-header">Trang chủ</h1>
                </div>
                <!-- /.col-lg-12 -->
            </div>
            <!-- /.row -->
            <div class="row">
              
                <div class="col-lg-4 col-md-6">
                    <div class="panel panel-green">
                        <div class="panel-heading">
                            <div class="row">
                                <div class="col-xs-3">
                                    <i class="fa fa-bolt fa-5x"></i>
                                </div>
                                <div class="col-xs-9 text-right">
                                    <div class="huge">
                                       <?php
                                           $con=mysqli_connect("mysql06.dotvndns.vn","tranc147_luan172","Luan123","tranc147_data1");  
                                           $result =mysqli_query($con,'SELECT value FROM congsuat1 ORDER BY id DESC LIMIT 1');
                                           $row = mysqli_fetch_array($result);
                                           echo "<td width='200px'>".$row['value']." kW"."</td>";
                                           mysqli_close($con);
                                        ?>  
                                    </div>
                                    <div>Công suất hiện tại</div>
                                </div>
                            </div>
                        </div>
                        
                    </div>
                </div>
                 <div class="col-lg-4 col-md-6">
                    <div class="panel panel-red">
                        <div class="panel-heading">
                            <div class="row">
                                <div class="col-xs-3">
                                    <i class="fa fa-signal fa-5x"></i>
                                </div>
                                <div class="col-xs-9 text-right">
                                    <div class="huge">
                                        <?php
                                           $con=mysqli_connect("mysql06.dotvndns.vn","tranc147_luan172","Luan123","tranc147_data1");
                                           $now = date("Y-m-d H:i:s");
                                           $now2 = date("Y-m-d 0:0:0"); 
                                           $result = mysqli_query($con,'SELECT value FROM nangluong ORDER BY id DESC LIMIT 1');
                                           $row = mysqli_fetch_row($result);
                                           $result1 =mysqli_query($con,"SELECT value FROM nangluong where timestamp <= '$now' and timestamp >= '$now2'");
                                           $row1 = mysqli_fetch_row($result1);
                                           $kq=$row[0] -$row1[0];
                                           echo "<td width='250px'>".round($kq,3)." kWh"."</td>";
                                           mysqli_close($con);
                                        ?>
                                    </div>
                                    <div>Năng lượng trong ngày</div>
                                </div>
                            </div>
                        </div>
                       
                    </div>
                </div>
                <div class="col-lg-4 col-md-6">
                    <div class="panel panel-yellow">
                        <div class="panel-heading">
                            <div class="row">
                                <div class="col-xs-2">
                                    <i class="fa fa-fire fa-5x"></i>
                                </div>
                                <div class="col-xs-10 text-right">
                                    <div class="huge">
                                        <?php
                                           $con=mysqli_connect("mysql06.dotvndns.vn","tranc147_luan172","Luan123","tranc147_data1");  
                                           $result =mysqli_query($con,'SELECT value FROM nangluong ORDER BY id DESC LIMIT 1');
                                           $row = mysqli_fetch_array($result);
                                           echo "<td width='250px'>".round($row['value']/1000,3)." MWh"."</td>";
                                           mysqli_close($con);
                                        ?> 
                                    </div>
                                    <div>Tổng năng lượng </div>
                                </div>
                            </div>
                        </div>
                       
                    </div>
                </div>
               
                <div class="col-lg-4 col-md-6">
                    <div class="panel panel-green">
                        <div class="panel-heading">
                            <div class="row">
                                <div class="col-xs-2">
                                    <i class="fa fa-envira fa-5x"></i>
                                </div>
                                <div class="col-xs-10 text-right">
                                    <div class="huge">
                                        <?php
                                           $con=mysqli_connect("mysql06.dotvndns.vn","tranc147_luan172","Luan123","tranc147_data1");  
                                           $result =mysqli_query($con,'SELECT value FROM nangluong ORDER BY id DESC LIMIT 1');
                                           $row = mysqli_fetch_array($result);
                                           echo "<td width='250px'>".round($row['value']*0.7/1000,3)." tấn"."</td>";
                                           mysqli_close($con);
                                        ?> 
                                    </div>
                                    <div>CO2 giảm </div>
                                </div>
                            </div>
                        </div>
                       
                    </div>
                </div>
                  <div class="col-lg-4 col-md-6">
                    <div class="panel panel-primary">
                        <div class="panel-heading">
                            <div class="row">
                                <div class="col-xs-3">
                                    <i class="fa fa-stack-exchange fa-5x"></i>
                                </div>
                                <div class="col-xs-9 text-right">
                                    <div class="huge">
                                        <?php
                                           $con=mysqli_connect("mysql06.dotvndns.vn","tranc147_luan172","Luan123","tranc147_data1");  
                                           $result =mysqli_query($con,'SELECT value FROM dienap1 ORDER BY id DESC LIMIT 1');
                                           //$result = mysqli_query($con,'SELECT * FROM dongdien ORDER BY id DESC');
    
                                             //while($row = mysqli_fetch_array($result))
                                             //{      
                                               //echo "<tr>";
                                               //echo "<td>" . $row['id'] . "</td>";
                                               //echo "<td>" . $row['time'] . "</td>";
                                               //echo "<td>" . $row['value'] . "</td>";
                                               //echo "</tr>";
        
                                             //}
                                           $row = mysqli_fetch_array($result);
                                           echo "<td width='200px'>".$row['value']." V"."</td>";
                                           mysqli_close($con);
                                        ?> 
                                    </div>
                                    <div>Điện áp</div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="col-lg-4 col-md-6">
                    <div class="panel panel-red">
                        <div class="panel-heading">
                            <div class="row">
                                <div class="col-xs-3">
                                    <i class="fa fa-support fa-5x"></i>
                                </div>
                                <div class="col-xs-9 text-right">
                                    <div class="huge">
                                       <?php
                                           $con=mysqli_connect("mysql06.dotvndns.vn","tranc147_luan172","Luan123","tranc147_data1");  
                                           $result =mysqli_query($con,'SELECT value FROM dongdien1 ORDER BY id DESC LIMIT 1');
                                           $row = mysqli_fetch_array($result);
                                           echo "<td width='200px'>".$row['value']." A"."</td>";
                                           mysqli_close($con);
                                        ?> 
                                    </div>
                                    <div>Dòng Điện</div>
                                </div>
                            </div>
                        </div>
                       
                    </div>
                </div>
            </div>
            <!-- /.row -->
            <div class="row">
                <div class="col-lg-12">
                    <div class="panel panel-default">
                        <div class="panel-heading">
                            <i class="fa fa-bar-chart-o fa-fw"></i> Đồ thị công suất tạo ra 
                            <div class="pull-right">
                                <div class="btn-group">
                                    <button type="button" class="btn btn-default btn-xs dropdown-toggle" data-toggle="dropdown">
                                        Actions
                                        <span class="caret"></span>
                                    </button>
                                    <ul class="dropdown-menu pull-right" role="menu">
                                        <li><a href="#">Action</a>
                                        </li>
                                        <li><a href="#">Another action</a>
                                        </li>
                                        <li><a href="#">Something else here</a>
                                        </li>
                                        <li class="divider"></li>
                                        <li><a href="#">Separated link</a>
                                        </li>
                                    </ul>
                                </div>
                            </div>
                        </div>
                        <!-- /.panel-heading -->
                        <div class="panel-body">
                            <div id="morris-area-chart1">

                               
                            </div>
                        </div>
                        <!-- /.panel-body -->
                    </div>
                    
                    <!-- /.panel -->
            
                </div>
            </div>
           
        </div>
        <!-- /#page-wrapper -->

    </div>
    <!-- /#wrapper -->

    <!-- jQuery -->
    
    <script src="../vendor/jquery/jquery.min.js"></script>

    <!-- Bootstrap Core JavaScript -->
    <script src="../vendor/bootstrap/js/bootstrap.min.js"></script>

    <!-- Metis Menu Plugin JavaScript -->
    <script src="../vendor/metisMenu/metisMenu.min.js"></script>

    <!-- Morris Charts JavaScript -->
    <script src="../vendor/raphael/raphael.min.js"></script>
    <script src="../vendor/morrisjs/morris.min.js"></script>
    <script src="../data/morris-data.js"></script>
    <script src="../data/morris-data-nl.js"></script>
     <!-- Custom Theme JavaScript -->
    <script src="../dist/js/sb-admin-2.js"></script>

</body>

</html>
