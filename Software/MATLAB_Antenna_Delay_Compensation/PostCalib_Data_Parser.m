rootDir = 'DronPrecalib_Data/Raw_Data/';

folders = {'D0'};

pairs = {
    {'U0', 'U1', 'U2', 'U3'}
};

%% Process p1, p2
for p = 1:2

    mergedData = [];
    columnNames = {};

    for u = 1:length(folders)

        folder = fullfile(rootDir, folders{u});
        folderPairs = pairs{u};

        for pairIdx = 1:length(folderPairs)

            pair = folderPairs{pairIdx};

            for v = 1:10

                filename = sprintf('%s_v%d_p%d.csv', pair, v, p);
                filepath = fullfile(folder, filename);

                data = readmatrix(filepath);
                data = data(:);

                mergedData(:, end+1) = data;

                columnNames{end+1} = sprintf('%s_v%d', pair, v);
            end
        end
    end

    T = array2table(mergedData, ...
        'VariableNames', columnNames);

    outputFile = fullfile(rootDir, sprintf('merged_p%d.csv', p));
    writetable(T, outputFile);

    fprintf('Created %s: %d rows x %d columns\n', ...
        outputFile, height(T), width(T));
end



%% Process actual distances
% p1_offset_distance = 0.025*2; % UWB
% p2_offset_distance = 0.025*2; % UWB
% p3_offset_distance = 0.025+0.01; % UWB

p1_drone_offset_distance = 0.025 + 0.06; % DRON
p2_drone_offset_distance = 0.025 + 0.07; % DRON

D0_raw_distances = readmatrix(fullfile(rootDir, "Raw_Distances\D0_Raw_Distances.csv"));
D0_p1_distances = D0_raw_distances + p1_drone_offset_distance;
D0_p2_distances = D0_raw_distances + p2_drone_offset_distance;

P1_drone_distances = [D0_p1_distances];
P1_drone_distances_table = array2table(P1_drone_distances, ...
    'VariableNames', {'D0'});

P2_drone_distances = [D0_p2_distances];
P2_drone_distances_table = array2table(P2_drone_distances, ...
    'VariableNames', {'D0'});



% 
% U0_post_distances = readmatrix(fullfile(rootDir, "Raw_Distances\U0_distances.csv"));
% U0_p1_distances = U0_post_distances + p1_offset_distance;
% U0_p2_distances = U0_post_distances + p2_offset_distance;
% U0_p3_distances = U0_post_distances + p3_offset_distance;
% 
% U1_post_distances = readmatrix(fullfile(rootDir, "Raw_Distances\U1_distances.csv"));
% U1_p1_distances = U1_post_distances + p1_offset_distance;
% U1_p2_distances = U1_post_distances + p2_offset_distance;
% U1_p3_distances = U1_post_distances + p3_offset_distance;
% 
% U2_post_distances = readmatrix(fullfile(rootDir, "Raw_Distances\U2_distances.csv"));
% U2_p1_distances = U2_post_distances + p1_offset_distance;
% U2_p2_distances = U2_post_distances + p2_offset_distance;
% U2_p3_distances = U2_post_distances + p3_offset_distance;
% 
% P1_distances = [U0_p1_distances, U0_p1_distances, U0_p1_distances, U1_p1_distances, U1_p1_distances, U2_p1_distances];
% P1_distances_table = array2table(P1_distances, ...
%     'VariableNames', {'U0U1', 'U0U2', 'U0U3', 'U1U2', 'U1U3', 'U2U3'});
% 
% P2_distances = [U0_p2_distances, U0_p2_distances, U0_p2_distances, U1_p2_distances, U1_p2_distances, U2_p2_distances];
% P2_distances_table = array2table(P2_distances, ...
%     'VariableNames', {'U0U1', 'U0U2', 'U0U3', 'U1U2', 'U1U3', 'U2U3'});
% 
% P3_distances = [U0_p3_distances, U0_p3_distances, U0_p3_distances, U1_p3_distances, U1_p3_distances, U2_p3_distances];
% P3_distances_table = array2table(P3_distances, ...
%     'VariableNames', {'U0U1', 'U0U2', 'U0U3', 'U1U2', 'U1U3', 'U2U3'});

%% Saves
save_ps = false;
if save_ps % Uwaga na folder!
    writetable(P1_distances_table, 'PostCalib_Data_v2/Actual_Distances/P1_actual_distances.csv');
    writetable(P2_distances_table, 'PostCalib_Data_v2/Actual_Distances/P2_actual_distances.csv');
    % writetable(P3_distances_table, 'PostCalib_Data/Actual_Distances/P3_actual_distances.csv');
end


save_ps = true;
if save_ps % Uwaga na folder!
    writetable(P1_drone_distances_table, 'DronPrecalib_Data/Actual_Distances/P1_actual_distances.csv');
    writetable(P2_drone_distances_table, 'DronPrecalib_Data/Actual_Distances/P2_actual_distances.csv');
    % writetable(P3_distances_table, 'PostCalib_Data/Actual_Distances/P3_actual_distances.csv');
end