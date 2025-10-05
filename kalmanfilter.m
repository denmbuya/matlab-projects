function y = kalmanfilter(z)
%#codegen
dt = 1;
% Initialize state transition matrix
A=[ 1 0 dt 0 0 0;...     % [x  ]            
       0 1 0 dt 0 0;...     % [y  ]
       0 0 1 0 dt 0;...     % [Vx]
       0 0 0 1 0 dt;...     % [Vy]
       0 0 0 0 1 0 ;...     % [Ax]
       0 0 0 0 0 1 ];       % [Ay]
H = [1 0 0 0 0 0 0; 0 1 0 0 0 0]; %initialize measurement matrix
Q = eye(6);
R = 1000*eye(2);

persistent x_est p_est
if isempty(x_est)
    x_est = zeros(6,1)
    p_est = zeros(6,6)
end

%predicted state of covariance
x_prd = A*x_est;
p_prd = A * p_est * A' + Q;
% Estimation
S = H * p_prd' * H' + R;
B = H * p_prd';
klm_gain = (S \ B)';
% Estimated state and covariance
x_est = x_prd + klm_gain * (z - H * x_prd);
p_est = p_prd - klm_gain * H * p_prd;
% Compute the estimated measurements
y = H * x_est;
end                % of the function

load position_data.mat
hold; grid;

for idx = 1: numPts
z = position(:,idx);
plot(z(1), z(2), 'bx');
axis([-1 1 -1 1]);
end
title('Test vector for the Kalman filtering with 2 sudden discontinuities ');
xlabel('x-axis');ylabel('y-axis');
hold;