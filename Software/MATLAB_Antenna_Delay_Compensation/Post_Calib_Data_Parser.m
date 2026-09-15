%% Settings
rootDir = 'PostCalib_Data/';

folders = {'U0', 'U1', 'U2'};
pairs   = {'U0U1', 'U1U2', 'U2U3'};

%% Process p1, p2, p3
for p = 1:3

    mergedData = [];
    columnNames = {};

    for u = 1:3

        folder = fullfile(rootDir, folders{u});
        pair = pairs{u};

        % v1 ... v10
        for v = 1:10

            filename = sprintf('%s_v%d_p%d.csv', pair, v, p);
            filepath = fullfile(folder, filename);

            % Read the 100 measurements
            data = readmatrix(filepath);

            % Make sure it is a column
            data = data(:);

            % Add measurements as a new column
            mergedData(:, end+1) = data;

            % Column name
            columnNames{end+1} = sprintf('%s_v%d', pair, v);
        end
    end

    % Convert to table
    T = array2table(mergedData, ...
        'VariableNames', columnNames);

    % Save
    outputFile = fullfile(rootDir, sprintf('merged_p%d.csv', p));
    writetable(T, outputFile);

    fprintf('Created %s: %d rows x %d columns\n', ...
        outputFile, height(T), width(T));
end
