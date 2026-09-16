rootDir = 'PostCalib_Data/Raw_Data/';

folders = {'U0', 'U1', 'U2'};

pairs = {
    {'U0U1', 'U0U2', 'U0U3'}, ...
    {'U1U2', 'U1U3'}, ...
    {'U2U3'} ...
};

%% Process p1, p2, p3
for p = 1:3

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
p1_offset_distance = 0.025*2;
p2_offset_distance = 0.025*2;
p3_offset_distance = 0.025+0.01;

U0_post_distances = readmatrix("PostCalib_Data\Raw_Data\Raw_Distances\U0_distances.csv");
U0_p1_distances = U0_post_distances + p1_offset_distance;
U0_p2_distances = U0_post_distances + p2_offset_distance;
U0_p3_distances = U0_post_distances + p3_offset_distance;

U1_post_distances = readmatrix("PostCalib_Data\Raw_Data\Raw_Distances\U1_distances.csv");
U1_p1_distances = U1_post_distances + p1_offset_distance;
U1_p2_distances = U1_post_distances + p2_offset_distance;
U1_p3_distances = U1_post_distances + p3_offset_distance;

U2_post_distances = readmatrix("PostCalib_Data\Raw_Data\Raw_Distances\U2_distances.csv");
U2_p1_distances = U2_post_distances + p1_offset_distance;
U2_p2_distances = U2_post_distances + p2_offset_distance;
U2_p3_distances = U2_post_distances + p3_offset_distance;

P1_distances = [U0_p1_distances, U1_p1_distances, U2_p1_distances];
P1_distances_table = array2table(P1_distances, ...
    'VariableNames', {'U0', 'U1', 'U2'});

P2_distances = [U0_p2_distances, U1_p2_distances, U2_p2_distances];
P2_distances_table = array2table(P2_distances, ...
    'VariableNames', {'U0', 'U1', 'U2'});

P3_distances = [U0_p3_distances, U1_p3_distances, U2_p3_distances];
P3_distances_table = array2table(P3_distances, ...
    'VariableNames', {'U0', 'U1', 'U2'});

writetable(P1_distances_table, 'PostCalib_Data/Actual_Distances/P1_actual_distances.csv');
writetable(P2_distances_table, 'PostCalib_Data/Actual_Distances/P2_actual_distances.csv');
writetable(P3_distances_table, 'PostCalib_Data/Actual_Distances/P3_actual_distances.csv');