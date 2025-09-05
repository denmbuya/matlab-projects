% Code to plot simulation results from MassSpringDamperInSimulinkAndSimscape

% Copyright 2015 The MathWorks, Inc.

% Reuse figure if it exists, else create new figure
try
    figure(h1_MassSpringDamperInSimulinkAndSimscape)
catch
    h1_MassSpringDamperInSimulinkAndSimscape=figure('Name', 'MassSpringDamperInSimulinkAndSimscape');
end

% Generate simulation results if they don't exist
if(~exist('simlog_MassSpringDamperInSimulinkAndSimscape','var'))
    sim('MassSpringDamperInSimulinkAndSimscape')
end

% Get simulation results
temp_x1_sl=get(logsout_MassSpringDamperInSimulinkAndSimscape,'m1_h_sl');    % Simulink
temp_x1_sc=simlog_MassSpringDamperInSimulinkAndSimscape.Spring.x.series;    % Simscape

% Plot results
plot(temp_x1_sc.time,temp_x1_sc.values,'LineWidth',3)
hold on
plot(temp_x1_sl.Values.Time,temp_x1_sl.Values.Data,'c--','LineWidth',1)
hold off
grid on
xlabel('Time (s)');
ylabel('Position (m)');
title('Position of Mass');
legend({'Simscape','Simulink'},'Location','Best');

% Remove temporary variables
clear temp_x1_sl temp_x1_sc
